/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:34:08 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/23 19:16:00 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <time.h>
#include "server.h"
#include <errno.h>

#define TICK_RATE 30  // Updates per second
#define TICK_INTERVAL_USEC (1000000 / TICK_RATE)

// Make socket non-blocking
static int set_nonblocking(int socket_fd)
{
    int flags = fcntl(socket_fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        return -1;
    }
    
    if (fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL O_NONBLOCK");
        return -1;
    }
    
    return 0;
}

// Apply all socket optimizations
static int optimize_socket(int socket_fd)
{
    int yes = 1;
    int send_buffer_size = 8192;
    int recv_buffer_size = 8192;

    // Disable Nagle's algorithm
    if (setsockopt(socket_fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) < 0) {
        perror("setsockopt TCP_NODELAY");
        return -1;
    }

    // Set buffer sizes
    if (setsockopt(socket_fd, SOL_SOCKET, SO_SNDBUF, &send_buffer_size, sizeof(send_buffer_size)) < 0) {
        perror("setsockopt SO_SNDBUF");
        return -1;
    }
    
    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, &recv_buffer_size, sizeof(recv_buffer_size)) < 0) {
        perror("setsockopt SO_RCVBUF");
        return -1;
    }

    // Make non-blocking
    if (set_nonblocking(socket_fd) < 0) {
        return -1;
    }
    
    return 0;
}

static void deconnect_client(struct pollfd *pollfds, int *client_count, int who_left)
{
    printf("Client %d disconnected\n", who_left);
    close(pollfds[who_left].fd);
    
    for (int i = who_left; i < *client_count - 1; i++) {
        pollfds[i] = pollfds[i + 1];
    }

    (*client_count)--;
    pollfds[*client_count].fd = -1;
    pollfds[*client_count].revents = 0;
}

int init_server(t_server *server)
{
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd <= 0) {
        perror("socket failed");
        return (FAIL);
    }
    
    // Allow socket reuse to avoid "address already in use" errors
    int opt = 1;
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt SO_REUSEADDR");
        return (FAIL);
    }
    
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(PORT);
    
    if (bind(server->server_fd, (struct sockaddr *)&server->address, sizeof(server->address)) < 0) {
        perror("bind failed");
        return (FAIL);
    }
    
    if (listen(server->server_fd, MAX_PLAYERS) < 0) {
        perror("listen failed");
        return (FAIL);
    }
    
    // Make server socket non-blocking
    if (set_nonblocking(server->server_fd) < 0) {
        return (FAIL);
    }
    
    return (SUCCESS);
}

static void init_poll(t_server *server, struct pollfd *server_poll)
{
    server_poll->fd = server->server_fd;
    server_poll->events = POLLIN;
    server_poll->revents = 0;
}

// Read with proper TCP fragmentation handling
ssize_t read_complete(int fd, void *buffer, size_t length)
{
    char *buf = (char*)buffer;
    
    // For non-blocking sockets, try once and return whatever we get
    ssize_t bytes_read = read(fd, buf, length);
    if (bytes_read <= 0) {
        return bytes_read; // Error or no data
    }
    
    return bytes_read;
}

int server_wait_loop(t_server *server)
{
    struct pollfd server_poll = {0};
    t_packet packet = {0};
    uint32_t sequence = 0;
    
    // Setup polling
    init_poll(server, &server_poll);
    server->pollfds[server->client_count++] = server_poll;
    
    // Initialize timing variables
    struct timeval last_tick;
    gettimeofday(&last_tick, NULL);
    
    while (1) {
        struct timeval now;
        gettimeofday(&now, NULL);
        
        // Calculate time elapsed since last tick (in microseconds)
        long elapsed_usec = (now.tv_sec - last_tick.tv_sec) * 1000000 + 
                           (now.tv_usec - last_tick.tv_usec);
        
        // Calculate time remaining until next tick
        int poll_timeout = (elapsed_usec >= TICK_INTERVAL_USEC) ? 
                            0 : (TICK_INTERVAL_USEC - elapsed_usec) / 1000;
        
        // Cap poll timeout to reasonable value
        if (poll_timeout > 50) poll_timeout = 50;
        
        // Wait for events or timeout
        int poll_result = poll(server->pollfds, server->client_count, poll_timeout);
        
        // Process all client activity
        if (poll_result > 0) {
            for (int i = 0; i < server->client_count; i++) {
                if (!(server->pollfds[i].revents & POLLIN)) {
                    continue;  // No activity for this client
                }
                
                // Clear revents flag immediately
                server->pollfds[i].revents = 0;
                
                if (i == 0) {
                    // Server socket - handle new connection
                    server->address_len = sizeof(server->address);
                    int new_client_fd = accept(server->server_fd,
                                       (struct sockaddr *)&server->address,
                                       (socklen_t *)&server->address_len);
                    
                    if (new_client_fd < 0) {
                        if (errno != EAGAIN && errno != EWOULDBLOCK) {
                            perror("accept failed");
                        }
                        continue;
                    }
                    
                    // Optimize new client socket
                    if (optimize_socket(new_client_fd) < 0) {
                        close(new_client_fd);
                        continue;
                    }
                    
                    printf("New client connected (fd=%d)\n", new_client_fd);
                    
                    server_poll.fd = new_client_fd;
                    server_poll.events = POLLIN;
                    server_poll.revents = 0;
                    server->pollfds[server->client_count++] = server_poll;
                }
                else {
                    // Client socket - handle data
                    int bytes_read = read_complete(server->pollfds[i].fd, &packet, sizeof(t_packet));
                    
                    if (bytes_read <= 0) {
                        if (bytes_read < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
                            // No data available, not an error
                            continue;
                        }
                        
                        // Disconnection or error
                        deconnect_client(server->pollfds, &server->client_count, i);
                        i--; // Adjust index since we removed an element
                        continue;
                    }
                    
                    // Process received data here
                    // ...
                }
            }
        }
        
        // Check if it's time for a game tick
        if (elapsed_usec >= TICK_INTERVAL_USEC) {
            // Update game state here
            // ...
            
            // Send updates to all clients
            sequence++; // Increment sequence for this update batch
            
            for (int i = 1; i < server->client_count; i++) {
                packet.id = i;
                
                // Non-blocking send may not send everything
                int bytes_sent = send(server->pollfds[i].fd, &packet, sizeof(packet), 
                                     MSG_DONTWAIT | MSG_NOSIGNAL);
                
                if (bytes_sent < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
                    // Real error - disconnect client
                    perror("send");
                    deconnect_client(server->pollfds, &server->client_count, i);
                    i--; // Adjust index
                }
            }
            
            // Reset tick timer
            gettimeofday(&last_tick, NULL);
        }
        
        // Optional: Add a small sleep to prevent CPU thrashing if needed
        // usleep(1000); // 1ms
    }
}

int main()
{
    t_server server = {0};

    if (init_server(&server) == FAIL) {
        return 1;
    }
    
    printf("Server started on port %d\n", PORT);
    server_wait_loop(&server);
    
    return 0;
}

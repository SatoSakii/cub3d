/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:34:08 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/21 10:26:18 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"

static void deconnect_client(struct pollfd *pollfds, int *client_count, int who_left)
{
    close(pollfds[who_left].fd); // Ferme le socket du client déconnecté
    for (int i = who_left; i < *client_count - 1; i++)
        pollfds[i] = pollfds[i + 1]; // Décale les entrées dans pollfds

    (*client_count)--;
    pollfds[*client_count].fd = -1;  // Met un fd invalide
    pollfds[*client_count].revents = 0; // Reset revents
}

int	init_server(t_server *server)
{
	server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server->server_fd == 0)
	{
		perror("socket failed");
		return (FAIL);
	}
	server->address.sin_family = AF_INET;
	server->address.sin_addr.s_addr = INADDR_ANY;
	server->address.sin_port = htons(PORT);
	if (bind(server->server_fd
			, (struct sockaddr *)&server->address, sizeof(server->address)) < 0)
	{
		perror("bind failed");
		return (FAIL);
	}
	if (listen(server->server_fd, MAX_PLAYERS) < 0)
	{
		perror("listen failed");
		return (FAIL);
	}
	return (SUCCESS);
}

static void	init_poll(t_server *server, struct pollfd *server_poll)
{
	server_poll->fd = server->server_fd;
	server_poll->events = POLLIN;
	server_poll->revents = 0;
}

int	server_wait_loop(t_server *server)
{
	struct pollfd	server_poll = {0};
	t_packet		packet = {0};

	init_poll(server, &server_poll);
	server->pollfds[server->client_count++] = server_poll;

	while (1)
	{
		poll(server->pollfds, server->client_count, -1);
		printf("Clients actifs : %d\n", server->client_count);
		
		int i = 0;

		while (i < server->client_count)
		{
			if (server->pollfds[i].revents & POLLIN)
			{
				if (i == 0)
				{
				server->address_len = sizeof(server->address);
				 int new_client_fd = accept(server->server_fd
									, (struct sockaddr *restrict)&server->address
									, (socklen_t *restrict)&server->address_len);
					if (new_client_fd < 0)
					{
						perror("failed accept");
						return (FAIL);
					}
					server_poll.fd = new_client_fd;
					server_poll.events = POLLIN;  // ✅ Important
					server->pollfds[server->client_count++] = server_poll;
					break ;
				}
				else
				{
					int bytes_read = read(server->pollfds[i].fd, &packet, sizeof(t_packet));
					if (bytes_read == 0)
					{
						deconnect_client(server->pollfds, &server->client_count , i);
						continue ;
					}
					i++;
				}
			}
			server->pollfds[i].revents = 0;
			i++;
		}
		i = 1;
		while (i < server->client_count)
		{
			send(server->pollfds[i].fd, &packet, sizeof(packet), MSG_CONFIRM);
			i++;
		}
	}
}

int main()
{
	t_server	server = {0};
	init_server(&server);
	server_wait_loop(&server);
}

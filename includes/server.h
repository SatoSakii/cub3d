/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:26:42 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/21 09:19:59 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdint.h>
# include <sys/socket.h>
# include <poll.h>
# include <arpa/inet.h>
# include <stdbool.h>

# define PORT 4241
# define MAX_PLAYERS 2

enum e_server_error
{
	FAIL = -1,
	SUCCESS,
};

typedef struct	__attribute__((packed))s_packet
{
	uint8_t			id;
	int16_t			px;
	int16_t			py;
	int16_t			wx;
	int16_t			wy;
	bool			shoot;
	uint8_t			speed;
}	t_packet;

typedef struct	s_server
{
	struct sockaddr_in	address;
	int					address_len;
	int					server_fd;
	int					client_count;
	struct pollfd		pollfds[MAX_PLAYERS + 1];
}	t_server;

int	init_server(t_server *server);
int	server_wait_loop(t_server *server);


#endif

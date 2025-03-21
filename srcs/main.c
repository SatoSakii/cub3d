/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 00:23:18 by albernar          #+#    #+#             */
/*   Updated: 2025/03/21 10:07:30 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <sys/socket.h>

int	parse_file(int argc, char **argv, t_error_ctx *ctx, t_game *game)
{
	int	err;
	int	fd;

	err = validate_argument_count(argc, argv, ctx);
	if (err == PROCESS_ERR)
		return (PROCESS_ERR);
	err = validate_file_extension(ctx);
	if (err == PROCESS_ERR)
		return (PROCESS_ERR);
	fd = validate_open_file(ctx);
	if (fd == PROCESS_ERR)
		return (PROCESS_ERR);
	err = parse_data(fd, ctx);
	if (err == PROCESS_ERR)
	{
		free_game(game);
		close(fd);
		return (err);
	}
	err = parse_map(fd, ctx, game);
	if (err == PROCESS_ERR)
		free_game(game);
	close(fd);
	return (err);
}

int	main(int argc, char **argv)
{
	t_error_ctx	ctx;
	t_game		game;

	init_game(&game, &ctx);
	if (parse_file(argc, argv, &ctx, &game))
		return (1);
	if (init_mlx(&game, &game.mlx) == PROCESS_ERR)
	{
		free_game(&game);
		return (1);
	}
	if ((game.client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return -1;
	}
	game.packet = (t_packet){0};
	game.serv_addr.sin_family = AF_INET;
	game.serv_addr.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &game.serv_addr.sin_addr) <= 0)
	{
		perror("inet_pton");
		return -1;
	}
	if (connect(game.client_socket, (struct sockaddr *)&game.serv_addr, sizeof(game.serv_addr)) < 0)
	{
		perror("connect");
		return -1;
	}
	mlx_set_fps_goal(game.mlx.ctx, 60);
	mlx_on_event(game.mlx.ctx, game.mlx.win, MLX_KEYDOWN, event_keydown, &game);
	mlx_on_event(game.mlx.ctx, game.mlx.win, MLX_KEYUP, event_keyup, &game);
	mlx_add_loop_hook(game.mlx.ctx, event_loop, &game);
	mlx_loop(game.mlx.ctx);
	free_game(&game);
	return (0);
}

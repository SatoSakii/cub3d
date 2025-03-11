/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 00:23:18 by albernar          #+#    #+#             */
/*   Updated: 2025/03/11 18:46:13 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_on_event(game.mlx.ctx, game.mlx.win, MLX_KEYDOWN, event_keydown, &game);
	mlx_on_event(game.mlx.ctx, game.mlx.win, MLX_KEYUP, event_keyup, &game);
	mlx_add_loop_hook(game.mlx.ctx, event_loop, &game);
	mlx_loop(game.mlx.ctx);
	free_game(&game);
	return (0);
}

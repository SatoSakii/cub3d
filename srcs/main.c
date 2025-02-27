/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:01:53 by albernar          #+#    #+#             */
/*   Updated: 2025/02/27 18:09:33 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "render.h"

int	parse_file(int argc, char **argv, t_error_ctx *ctx, t_game *game)
{
	int	err;
	int	fd;

	err = validate_argument_count(argc, argv, ctx);
	if (err)
		return (PROCESS_ERR);
	err = validate_file_extension(ctx);
	if (err)
		return (PROCESS_ERR);
	fd = validate_open_file(ctx);
	if (fd == PROCESS_ERR)
		return (PROCESS_ERR);
	err = parse_data(fd, ctx, game);
	if (err == PROCESS_ERR)
	{
		close(fd);
		return (PROCESS_ERR);
	}
	err = parse_map(fd, ctx, game);
	close(fd);
	return (err);
}



int	main(int argc, char **argv)
{
	t_error_ctx	ctx;
	t_game		game;

	game = (t_game){0};
	ctx = (t_error_ctx){0};
	ft_memset(&game.ceiling, -1, sizeof(game.ceiling));
	ft_memset(&game.floor, -1, sizeof(game.floor));
	if (parse_file(argc, argv, &ctx, &game) == PROCESS_ERR)
	{
		free_game(&game);
		return (1);
	}
	init_mlx(&game.mlx);
	mlx_on_event(game.mlx.mlx, game.mlx.win, MLX_KEYDOWN, key_hook, &game);
	cub_raycasting(&game);
	mlx_loop(game.mlx.mlx);
	mlx_destroy_window(game.mlx.mlx, game.mlx.win);
	mlx_destroy_context(game.mlx.mlx);
	free_game(&game);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:36:36 by albernar          #+#    #+#             */
/*   Updated: 2025/03/10 18:42:22 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game, t_error_ctx *ctx)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(ctx, 0, sizeof(t_error_ctx));
	ft_memset(&game->ceiling, -1, sizeof(t_colors));
	ft_memset(&game->floor, -1, sizeof(t_colors));
	register_tile("1");
	register_tile("0");
	register_direction("N");
	register_direction("S");
	register_direction("E");
	register_direction("W");
	register_color("F", &game->floor);
	register_color("C", &game->ceiling);
	register_texture("NO", &game->no);
	register_texture("SO", &game->so);
	register_texture("WE", &game->we);
	register_texture("EA", &game->ea);
}

static int	init_textures_regions(t_game *game, t_mlx *mlx)
{
	game->no.pixels = malloc(sizeof(mlx_color)
			* (game->no.width * game->no.height));
	game->so.pixels = malloc(sizeof(mlx_color)
			* (game->so.width * game->so.height));
	game->we.pixels = malloc(sizeof(mlx_color)
			* (game->we.width * game->we.height));
	game->ea.pixels = malloc(sizeof(mlx_color)
			* (game->ea.width * game->ea.height));
	if (!game->no.pixels || !game->so.pixels
		|| !game->we.pixels || !game->ea.pixels)
		return (PROCESS_ERR);
	mlx_get_image_region(mlx->ctx, game->no.img, 0, 0,
		game->no.width, game->no.height, game->no.pixels);
	mlx_get_image_region(mlx->ctx, game->so.img, 0, 0,
		game->so.width, game->so.height, game->so.pixels);
	mlx_get_image_region(mlx->ctx, game->we.img, 0, 0,
		game->we.width, game->we.height, game->we.pixels);
	mlx_get_image_region(mlx->ctx, game->ea.img, 0, 0,
		game->ea.width, game->ea.height, game->ea.pixels);
	return (PROCESS_OK);
}

int	init_textures(t_game *game, t_mlx *mlx)
{
	game->no.img = mlx_new_image_from_file(mlx->ctx, game->no.path,
			&game->no.width, &game->no.height);
	game->so.img = mlx_new_image_from_file(mlx->ctx, game->so.path,
			&game->so.width, &game->so.height);
	game->we.img = mlx_new_image_from_file(mlx->ctx, game->we.path,
			&game->we.width, &game->we.height);
	game->ea.img = mlx_new_image_from_file(mlx->ctx, game->ea.path,
			&game->ea.width, &game->ea.height);
	if (!game->no.img || !game->so.img || !game->we.img || !game->ea.img)
		return (PROCESS_ERR);
	return (init_textures_regions(game, mlx));
}

int	init_mlx(t_game *game, t_mlx *mlx)
{
	mlx->ctx = mlx_init();
	if (!mlx->ctx)
		return (PROCESS_ERR);
	mlx->info.title = "cub3D";
	mlx->info.width = WINDOW_WIDTH;
	mlx->info.height = WINDOW_HEIGHT;
	mlx->win = mlx_new_window(mlx->ctx, &mlx->info);
	if (!mlx->win)
		return (PROCESS_ERR);
	game->scene = malloc(sizeof(mlx_color) * WINDOW_WIDTH * WINDOW_HEIGHT);
	if (!game->scene)
		return (PROCESS_ERR);
	return (init_textures(game, mlx));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:37:45 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:27:23 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	get_textures_region(t_game *game, t_mlx *mlx)
{
	mlx_get_image_region(mlx->ctx, game->no.img, 0, 0,
		game->no.width, game->no.height, game->no.pixels);
	mlx_get_image_region(mlx->ctx, game->so.img, 0, 0,
		game->so.width, game->so.height, game->so.pixels);
	mlx_get_image_region(mlx->ctx, game->we.img, 0, 0,
		game->we.width, game->we.height, game->we.pixels);
	mlx_get_image_region(mlx->ctx, game->ea.img, 0, 0,
		game->ea.width, game->ea.height, game->ea.pixels);
	mlx_get_image_region(mlx->ctx, game->door.img, 0, 0,
		game->door.width, game->door.height, game->door.pixels);
	mlx_get_image_region(mlx->ctx, game->sprites[0].img, 0, 0,
		game->sprites[0].width, game->sprites[0].height,
		game->sprites[0].pixels);
	mlx_get_image_region(mlx->ctx, game->sprites[1].img, 0, 0,
		game->sprites[1].width, game->sprites[1].height,
		game->sprites[1].pixels);
	mlx_get_image_region(mlx->ctx, game->sprites[2].img, 0, 0,
		game->sprites[2].width, game->sprites[2].height,
		game->sprites[2].pixels);
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
	game->door.pixels = malloc(sizeof(mlx_color)
			* (game->door.width * game->door.height));
	game->sprites[0].pixels = malloc(sizeof(mlx_color)
			* (game->sprites[0].width * game->sprites[0].height));
	game->sprites[1].pixels = malloc(sizeof(mlx_color)
			* (game->sprites[1].width * game->sprites[1].height));
	game->sprites[2].pixels = malloc(sizeof(mlx_color)
			* (game->sprites[2].width * game->sprites[2].height));
	if (!game->no.pixels || !game->so.pixels
		|| !game->we.pixels || !game->ea.pixels || !game->door.pixels
		|| !game->sprites[0].pixels || !game->sprites[1].pixels
		|| !game->sprites[2].pixels)
		return (PROCESS_ERR);
	get_textures_region(game, mlx);
	return (PROCESS_OK);
}

static int	init_textures(t_game *game, t_mlx *mlx)
{
	game->no.img = mlx_new_image_from_file(mlx->ctx, game->no.path,
			&game->no.width, &game->no.height);
	game->so.img = mlx_new_image_from_file(mlx->ctx, game->so.path,
			&game->so.width, &game->so.height);
	game->we.img = mlx_new_image_from_file(mlx->ctx, game->we.path,
			&game->we.width, &game->we.height);
	game->ea.img = mlx_new_image_from_file(mlx->ctx, game->ea.path,
			&game->ea.width, &game->ea.height);
	game->door.img = mlx_new_image_from_file(mlx->ctx, game->door.path,
			&game->door.width, &game->door.height);
	game->sprites[0].img = mlx_new_image_from_file(mlx->ctx,
			game->sprites[0].path, &game->sprites[0].width,
			&game->sprites[0].height);
	game->sprites[1].img = mlx_new_image_from_file(mlx->ctx,
			game->sprites[1].path, &game->sprites[1].width,
			&game->sprites[1].height);
	game->sprites[2].img = mlx_new_image_from_file(mlx->ctx,
			game->sprites[2].path, &game->sprites[2].width,
			&game->sprites[2].height);
	if (!game->no.img || !game->so.img || !game->we.img || !game->ea.img
		|| !game->door.img || !game->sprites[0].img || !game->sprites[1].img
		|| !game->sprites[2].img)
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
	mlx_mouse_show(game->mlx.ctx);
	mlx_mouse_move(game->mlx.ctx, game->mlx.win,
		(WINDOW_WIDTH >> 1), (WINDOW_HEIGHT >> 1));
	init_renderer(&game->mlx);
	setup_imgui_style();
	mlx_set_fps_goal(mlx->ctx, DEFAULT_FPS_GOAL);
	return (init_textures(game, mlx));
}

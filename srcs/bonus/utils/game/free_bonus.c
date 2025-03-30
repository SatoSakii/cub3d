/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:30:33 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:27:21 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_imgs(t_game *game)
{
	if (game->no.img)
		mlx_destroy_image(game->mlx.ctx, game->no.img);
	if (game->so.img)
		mlx_destroy_image(game->mlx.ctx, game->so.img);
	if (game->we.img)
		mlx_destroy_image(game->mlx.ctx, game->we.img);
	if (game->ea.img)
		mlx_destroy_image(game->mlx.ctx, game->ea.img);
	if (game->door.img)
		mlx_destroy_image(game->mlx.ctx, game->door.img);
	if (game->sprites[0].img)
		mlx_destroy_image(game->mlx.ctx, game->sprites[0].img);
	if (game->sprites[1].img)
		mlx_destroy_image(game->mlx.ctx, game->sprites[1].img);
	if (game->sprites[2].img)
		mlx_destroy_image(game->mlx.ctx, game->sprites[2].img);
}

static void	free_pixels_tab(t_game *game)
{
	if (game->no.pixels)
		free(game->no.pixels);
	if (game->so.pixels)
		free(game->so.pixels);
	if (game->we.pixels)
		free(game->we.pixels);
	if (game->ea.pixels)
		free(game->ea.pixels);
	if (game->door.pixels)
		free(game->door.pixels);
	if (game->sprites[0].pixels)
		free(game->sprites[0].pixels);
	if (game->sprites[1].pixels)
		free(game->sprites[1].pixels);
	if (game->sprites[2].pixels)
		free(game->sprites[2].pixels);
}

static void	free_mlx(t_game *game)
{
	free_imgs(game);
	free_pixels_tab(game);
	if (game->scene)
		free(game->scene);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.ctx, game->mlx.win);
	if (game->mlx.ctx)
		mlx_destroy_context(game->mlx.ctx);
}

void	free_game(t_game *game)
{
	if (game->ea.addr)
		free(game->ea.addr);
	if (game->no.addr)
		free(game->no.addr);
	if (game->so.addr)
		free(game->so.addr);
	if (game->we.addr)
		free(game->we.addr);
	if (game->door.addr)
		free(game->door.addr);
	if (game->sprites[0].addr)
		free(game->sprites[0].addr);
	if (game->sprites[1].addr)
		free(game->sprites[1].addr);
	if (game->sprites[2].addr)
		free(game->sprites[2].addr);
	if (game->map.grid)
		ft_free2d((void **)game->map.grid);
	if (game->mlx.ctx && game->mlx.win)
		destroy_renderer(&game->mlx);
	free_mlx(game);
}

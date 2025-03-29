/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:30:33 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 03:38:57 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_mlx(t_game *game)
{
	if (game->no.img)
		mlx_destroy_image(game->mlx.ctx, game->no.img);
	if (game->so.img)
		mlx_destroy_image(game->mlx.ctx, game->so.img);
	if (game->we.img)
		mlx_destroy_image(game->mlx.ctx, game->we.img);
	if (game->ea.img)
		mlx_destroy_image(game->mlx.ctx, game->ea.img);
	if (game->no.pixels)
		free(game->no.pixels);
	if (game->so.pixels)
		free(game->so.pixels);
	if (game->we.pixels)
		free(game->we.pixels);
	if (game->ea.pixels)
		free(game->ea.pixels);
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
	if (game->map.grid)
		ft_free2d((void **)game->map.grid);
	if (game->mlx.ctx && game->mlx.win)
		destroy_renderer(&game->mlx);
	free_mlx(game);
}

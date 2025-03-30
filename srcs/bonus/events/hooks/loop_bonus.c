/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:04:07 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:26:48 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	event_loop(void *param)
{
	t_game		*game;
	double		delta_time;
	t_tribool	block;

	game = (t_game *)param;
	delta_time = get_delta_time();
	mlx_clear_window(game->mlx.ctx, game->mlx.win,
		(mlx_color){.rgba = 0x000000FF});
	block = block_game(game);
	raycast(game);
	if (block != TRIBOOL_TRUE)
		game_render(game, delta_time, block);
	print_fps();
}

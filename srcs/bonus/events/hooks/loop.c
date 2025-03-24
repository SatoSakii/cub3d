/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:04:07 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 15:31:38 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event_loop(void *param)
{
	t_game	*game;
	double	delta_time;

	game = (t_game *)param;
	delta_time = get_delta_time();
	mlx_clear_window(game->mlx.ctx, game->mlx.win,
		(mlx_color){.rgba = 0x000000FF});
	if (game->controls.keys[0].state == DOWN && !block_game(game))
		move_player(&game->player, MOVE_FORWARD);
	if (game->controls.keys[1].state == DOWN && !block_game(game))
		move_player(&game->player, MOVE_BACKWARD);
	if (game->controls.keys[2].state == DOWN && !block_game(game))
		move_player(&game->player, MOVE_LEFT);
	if (game->controls.keys[3].state == DOWN && !block_game(game))
		move_player(&game->player, MOVE_RIGHT);
	update_player(game, &game->player, delta_time);
	rotate_player(game, &game->player, delta_time);
	raycast(game);
	mlx_pixel_put_array(game->mlx.ctx, game->mlx.win,
		0, 0, game->scene, WINDOW_WIDTH * WINDOW_HEIGHT);
	print_fps();
}

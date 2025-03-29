/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:32:04 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 23:19:42 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_render(t_game *game, double delta_time, t_tribool block)
{
	if (game->controls.keys[0].state == DOWN && block == TRIBOOL_FALSE)
		move_player(&game->player, MOVE_FORWARD);
	if (game->controls.keys[1].state == DOWN && block == TRIBOOL_FALSE)
		move_player(&game->player, MOVE_BACKWARD);
	if (game->controls.keys[2].state == DOWN && block == TRIBOOL_FALSE)
		move_player(&game->player, MOVE_LEFT);
	if (game->controls.keys[3].state == DOWN && block == TRIBOOL_FALSE)
		move_player(&game->player, MOVE_RIGHT);
	update_player(game, &game->player, delta_time);
	rotate_player(game, &game->player, delta_time);
	print_minimap(game, 0b1010);
	mlx_pixel_put_array(game->mlx.ctx, game->mlx.win,
		0, 0, game->scene, WINDOW_WIDTH * WINDOW_HEIGHT);
}

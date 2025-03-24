/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:01:28 by albernar          #+#    #+#             */
/*   Updated: 2025/03/23 21:13:27 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_pos_collide(t_game *game, t_player *player, t_dvec2d pos)
{
	t_ivec2d	check_x;
	t_ivec2d	check_y;
	t_ivec2d	can_move;
	t_dvec2d	offset;

	offset.x = SLIDE_WALL_OFFSET * (1 - 2 * (pos.x < player->pos.x));
	offset.y = SLIDE_WALL_OFFSET * (1 - 2 * (pos.y < player->pos.y));
	check_x = (t_ivec2d){(int)floor(pos.x + offset.x),
		(int)floor(player->pos.y)};
	can_move.x = 1;
	if (check_x.x >= 0 && check_x.x < (int)game->map.width
		&& check_x.y >= 0 && check_x.y < (int)game->map.height
		&& game->map.grid[check_x.y][check_x.x] == '1')
		can_move.x = 0;
	check_y = (t_ivec2d){(int)floor(player->pos.x),
		(int)floor(pos.y + offset.y)};
	can_move.y = 1;
	if (check_y.x >= 0 && check_y.x < (int)game->map.width
		&& check_y.y >= 0 && check_y.y < (int)game->map.height
		&& game->map.grid[check_y.y][check_y.x] == '1')
		can_move.y = 0;
	if (can_move.x)
		player->pos.x = pos.x;
	if (can_move.y)
		player->pos.y = pos.y;
}

/*
	NOTE: MANDATORY DOESNT HAVE COLLISION
*/

void	update_pos(t_game *game, t_player *player, t_dvec3d pos)
{
	update_pos_collide(game, player, (t_dvec2d){pos.x, pos.y});
	player->pos.z = pos.z;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:01:28 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:28:27 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	check_possible_tile(t_game *game, t_ivec2d check, int *can_move)
{
	if (check.x >= 0 && check.x < (int)game->map.width
		&& check.y >= 0 && check.y < (int)game->map.height
		&& check.x < (int)ft_strlen(game->map.grid[check.y]))
	{
		if (game->map.grid[check.y][check.x] == '1')
			*can_move = 0;
		if (game->map.grid[check.y][check.x] == 'C')
			*can_move = 0;
		if (game->map.grid[check.y][check.x] == '2')
			*can_move = 0;
	}
}

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
	check_possible_tile(game, check_x, &can_move.x);
	check_y = (t_ivec2d){(int)floor(player->pos.x),
		(int)floor(pos.y + offset.y)};
	can_move.y = 1;
	check_possible_tile(game, check_y, &can_move.y);
	if (can_move.x)
		player->pos.x = pos.x;
	if (can_move.y)
		player->pos.y = pos.y;
}

void	update_pos(t_game *game, t_player *player, t_dvec3d pos)
{
	update_pos_collide(game, player, (t_dvec2d){pos.x, pos.y});
	player->pos.z = pos.z;
}

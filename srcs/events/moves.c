/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 03:22:23 by albernar          #+#    #+#             */
/*   Updated: 2025/03/11 16:55:56 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_pos(t_game *game, t_player *player, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x);
	map_y = (int)floor(y);
	if (game->collision && (map_x < 0 || map_x >= (int)game->map.width
			|| map_y < 0 || map_y >= (int)game->map.height))
	{
		player->pos.x = x;
		player->pos.y = y;
		return ;
	}
	if (game->collision && game->map.grid[map_y][map_x] == '1')
		return ;
	player->pos.x = x;
	player->pos.y = y;
}

void	move_player(t_game *game,
	t_player *player, int direction, double delta_time)
{
	t_dvec2d	new_pos;

	if (direction == MOVE_FORWARD)
	{
		new_pos.x = player->pos.x + player->dir.x * MOVE_SPEED * delta_time;
		new_pos.y = player->pos.y + player->dir.y * MOVE_SPEED * delta_time;
	}
	else if (direction == MOVE_BACKWARD)
	{
		new_pos.x = player->pos.x - player->dir.x * MOVE_SPEED * delta_time;
		new_pos.y = player->pos.y - player->dir.y * MOVE_SPEED * delta_time;
	}
	else if (direction == MOVE_LEFT)
	{
		new_pos.x = player->pos.x - player->dir.y * MOVE_SPEED * delta_time;
		new_pos.y = player->pos.y + player->dir.x * MOVE_SPEED * delta_time;
	}
	else if (direction == MOVE_RIGHT)
	{
		new_pos.x = player->pos.x + player->dir.y * MOVE_SPEED * delta_time;
		new_pos.y = player->pos.y - player->dir.x * MOVE_SPEED * delta_time;
	}
	update_pos(game, player, new_pos.x, new_pos.y);
}

#define MAX_PITCH 1080.0

void	rotate_player(t_game *game, t_player *player, double delta_time)
{
	t_ivec2d	mouse;
	t_dvec2d	ratio;
	double		old_dir_x;
	double		old_plane_x;
	double		pitch;

	mlx_mouse_get_pos(game->mlx.ctx, &mouse.x, &mouse.y);
	if (mouse.x < 0 || mouse.y < 0
		|| mouse.x > WINDOW_WIDTH || mouse.y > WINDOW_HEIGHT)
		return ;
	pitch = -(mouse.y - (WINDOW_HEIGHT / 2));
	game->camera_pitch += pitch;
	game->camera_pitch = fmax(fmin(game->camera_pitch, MAX_PITCH), -MAX_PITCH);
	ratio.x = cos((mouse.x - (WINDOW_WIDTH / 2)) * delta_time * -ROTATE_SPEED);
	ratio.y = sin((mouse.x - (WINDOW_WIDTH / 2)) * delta_time * -ROTATE_SPEED);
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * ratio.x - player->dir.y * ratio.y;
	player->dir.y = old_dir_x * ratio.y + player->dir.y * ratio.x;
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * ratio.x - player->plane.y * ratio.y;
	player->plane.y = old_plane_x * ratio.y + player->plane.y * ratio.x;
	mlx_mouse_move(game->mlx.ctx, game->mlx.win,
		WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

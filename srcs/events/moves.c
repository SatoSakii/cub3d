/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 03:22:23 by albernar          #+#    #+#             */
/*   Updated: 2025/03/13 14:04:29 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_pos_collision(t_game *game,
	t_player *player, double x, double y)
{
	t_ivec2d		check_x;
	t_ivec2d		check_y;
	t_ivec2d		can_move;
	t_dvec2d		offset;

	offset.x = OFFSET_SLIDE_WALL * (1 - 2 * (x < player->pos.x));
	offset.y = OFFSET_SLIDE_WALL * (1 - 2 * (y < player->pos.y));
	check_x = (t_ivec2d){(int)floor(x + offset.x), (int)floor(player->pos.y)};
	can_move.x = 1;
	if (check_x.x >= 0 && check_x.x < (int)game->map.width
		&& check_x.y >= 0 && check_x.y < (int)game->map.height
		&& game->map.grid[check_x.y][check_x.x] == '1')
		can_move.x = 0;
	check_y = (t_ivec2d){(int)floor(player->pos.x), (int)floor(y + offset.y)};
	can_move.y = 1;
	if (check_y.x >= 0 && check_y.x < (int)game->map.width
		&& check_y.y >= 0 && check_y.y < (int)game->map.height
		&& game->map.grid[check_y.y][check_y.x] == '1')
		can_move.y = 0;
	if (can_move.x)
		player->pos.x = x;
	if (can_move.y)
		player->pos.y = y;
}

static void	update_pos(t_game *game, t_player *player, double x, double y)
{
	if (!game->collision)
	{
		player->pos.x = x;
		player->pos.y = y;
		return ;
	}
	update_pos_collision(game, player, x, y);
}

void	move_player(t_game *game,
	t_player *player, int direction, double delta_time)
{
	t_dvec2d	new_pos;
	int			ms;

	ms = MOVE_SPEED + player->is_running * SPEED_FACTOR;
	if (direction == MOVE_FORWARD)
	{
		new_pos.x = player->pos.x + player->dir.x * ms * delta_time;
		new_pos.y = player->pos.y + player->dir.y * ms * delta_time;
	}
	else if (direction == MOVE_BACKWARD)
	{
		new_pos.x = player->pos.x - player->dir.x * ms * delta_time;
		new_pos.y = player->pos.y - player->dir.y * ms * delta_time;
	}
	else if (direction == MOVE_LEFT)
	{
		new_pos.x = player->pos.x - player->dir.y * ms * delta_time;
		new_pos.y = player->pos.y + player->dir.x * ms * delta_time;
	}
	else if (direction == MOVE_RIGHT)
	{
		new_pos.x = player->pos.x + player->dir.y * ms * delta_time;
		new_pos.y = player->pos.y - player->dir.x * ms * delta_time;
	}
	update_pos(game, player, new_pos.x, new_pos.y);
}

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

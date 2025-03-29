/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:22:45 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 04:11:38 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player(t_game *game, t_player *player, double delta_time)
{
	t_dvec3d	new_pos;

	update_velocity(player);
	new_pos = ft_dvec3d_add(player->pos,
			ft_dvec3d_scale(player->direction, player->velocity * delta_time));
	update_pos(game, player, new_pos);
	player->direction = (t_dvec3d){0, 0, 0};
}

void	update_velocity(t_player *player)
{
	double	step;
	double	max_speed;

	step = DEFAULT_STEP_SPEED;
	max_speed = DEFAULT_MAX_SPEED;
	if (player->is_running)
		max_speed = DEFAULT_MAX_SPEED_SPRINT;
	if (ft_dvec3d_norm(player->direction) > 0)
	{
		player->velocity += step;
		if (player->velocity > max_speed)
			player->velocity = max_speed;
	}
	else
	{
		player->velocity -= step;
		if (player->velocity < 0)
			player->velocity = 0;
	}
}

void	move_player(t_player *player, t_direction dir)
{
	if (dir == MOVE_FORWARD)
		player->direction = ft_dvec3d_add(player->direction,
				(t_dvec3d){player->dir.x, player->dir.y, 0});
	else if (dir == MOVE_BACKWARD)
		player->direction = ft_dvec3d_add(player->direction,
				(t_dvec3d){-player->dir.x, -player->dir.y, 0});
	else if (dir == MOVE_LEFT)
		player->direction = ft_dvec3d_add(player->direction,
				(t_dvec3d){-player->dir.y, player->dir.x, 0});
	else if (dir == MOVE_RIGHT)
		player->direction = ft_dvec3d_add(player->direction,
				(t_dvec3d){player->dir.y, -player->dir.x, 0});
	player->direction = ft_dvec3d_normalize(player->direction);
}

void	rotate_player(t_game *game, t_player *player, double delta_time)
{
	t_ivec2d	mouse_pos;
	t_dvec2d	ratio;
	double		tmp_value;
	double		pitch_up;

	mlx_mouse_get_pos(game->mlx.ctx, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x < 0 || mouse_pos.y < 0 || mouse_pos.x > WINDOW_WIDTH
		|| mouse_pos.y > WINDOW_HEIGHT || block_game(game) == TRIBOOL_UNSET)
		return ;
	pitch_up = -(mouse_pos.y - (WINDOW_HEIGHT >> 1));
	player->dir.z += pitch_up * player->sensitivity;
	player->dir.z = ft_dclamp(player->dir.z, -MAX_PITCH, MAX_PITCH);
	mouse_pos.x = (mouse_pos.x - (WINDOW_WIDTH >> 1)) * player->sensitivity
		* -DEFAULT_ROTATE_SPEED;
	ratio.x = cos(mouse_pos.x * delta_time);
	ratio.y = sin(mouse_pos.x * delta_time);
	tmp_value = player->dir.x;
	player->dir.x = player->dir.x * ratio.x - player->dir.y * ratio.y;
	player->dir.y = tmp_value * ratio.y + player->dir.y * ratio.x;
	tmp_value = player->plane.x;
	player->plane.x = player->plane.x * ratio.x - player->plane.y * ratio.y;
	player->plane.y = tmp_value * ratio.y + player->plane.y * ratio.x;
	mlx_mouse_move(game->mlx.ctx, game->mlx.win,
		(WINDOW_WIDTH >> 1), (WINDOW_HEIGHT >> 1));
}

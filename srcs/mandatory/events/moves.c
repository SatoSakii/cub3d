/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 03:22:23 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 18:12:27 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_player *player, int direction, double delta_time)
{
	if (direction == MOVE_FORWARD)
	{
		player->pos.x += player->dir.x * DEFAULT_MAX_SPEED * delta_time;
		player->pos.y += player->dir.y * DEFAULT_MAX_SPEED * delta_time;
	}
	else if (direction == MOVE_BACKWARD)
	{
		player->pos.x -= player->dir.x * DEFAULT_MAX_SPEED * delta_time;
		player->pos.y -= player->dir.y * DEFAULT_MAX_SPEED * delta_time;
	}
	else if (direction == MOVE_LEFT)
	{
		player->pos.x -= player->dir.y * DEFAULT_MAX_SPEED * delta_time;
		player->pos.y += player->dir.x * DEFAULT_MAX_SPEED * delta_time;
	}
	else if (direction == MOVE_RIGHT)
	{
		player->pos.x += player->dir.y * DEFAULT_MAX_SPEED * delta_time;
		player->pos.y -= player->dir.x * DEFAULT_MAX_SPEED * delta_time;
	}
}

void	rotate_player(t_player *player, int rotation, double delta_time)
{
	double	cos_rot;
	double	sin_rot;
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	if (rotation == ROTATION_LEFT)
	{
		cos_rot = cos(DEFAULT_ROTATE_SPEED * delta_time);
		sin_rot = sin(DEFAULT_ROTATE_SPEED * delta_time);
	}
	else
	{
		cos_rot = cos(-DEFAULT_ROTATE_SPEED * delta_time);
		sin_rot = sin(-DEFAULT_ROTATE_SPEED * delta_time);
	}
	player->dir.x = player->dir.x * cos_rot - player->dir.y * sin_rot;
	player->dir.y = old_dir_x * sin_rot + player->dir.y * cos_rot;
	player->plane.x = player->plane.x * cos_rot - player->plane.y * sin_rot;
	player->plane.y = old_plane_x * sin_rot + player->plane.y * cos_rot;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 05:47:45 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/29 06:14:21 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIMAP_R 100
#define SQUARE_SIZE 10

#include "cub3d.h"

void	rotate_point(t_dvec2d *m, float cx, float cy, float theta)
{
	t_dvec2d		d;

	d.x = m->x - cx;
	d.y = m->y - cy;
	m->x = cx + (d.x * cos(-theta) - d.y * sin(-theta));
	m->y = cy + (d.x * sin(-theta) + d.y * cos(-theta));
}

void	draw_minimap_background(t_game *game, int minimap_x, int minimap_y)
{
	t_ivec2d	d;
	int			index;

	d.y = -MINIMAP_R;
	while (d.y <= MINIMAP_R)
	{
		d.x = -MINIMAP_R;
		while (d.x <= MINIMAP_R)
		{
			if (d.x * d.x + d.y * d.y <= MINIMAP_R * MINIMAP_R)
			{
				index = (minimap_y + d.y) * WINDOW_WIDTH + (minimap_x + d.x);
				if (index >= 0 && index < WINDOW_WIDTH * WINDOW_HEIGHT)
					game->scene[index].rgba = 0x000000FF;
			}
			d.x++;
		}
		d.y++;
	}
}

static bool	is_valid_pixel(t_game *game, int index)
{
	return (index >= 0 && index < WINDOW_WIDTH * WINDOW_HEIGHT
		&& game->scene[index].rgba == 0x000000FF);
}

void	draw_square_line(t_game *game, t_minimap mini,
			bool flag, t_theta theta)
{
	t_dvec2d	y;
	t_ivec2d	p;
	int			index;

	ft_memset(&y, 0, sizeof(y));
	while (mini.tmp.y < SQUARE_SIZE)
	{
		p.x = (mini.m.x + mini.x.x - y.x);
		p.y = (mini.m.y + mini.x.y + y.y);
		index = p.y * WINDOW_WIDTH + p.x;
		if (!is_valid_pixel(game, index))
		{
			mini.tmp.y++;
			y.x += theta.sin_theta;
			y.y += theta.cos_theta;
			continue ;
		}
		if (flag)
			game->scene[index].rgba = 0x555C54FF;
		else
			game->scene[index].rgba = 0xF6F6DAFF;
		mini.tmp.y++;
		y.x += theta.sin_theta;
		y.y += theta.cos_theta;
	}
}

void	init_minimap(t_game *game, t_ivec2d *origin, t_ivec2d *map,
			float *player_angle, int pos)
{
	origin->x = game->player.pos.x * SQUARE_SIZE - MINIMAP_R;
	origin->y = game->player.pos.y * SQUARE_SIZE - MINIMAP_R;
	init_map_pos(game, map, pos);
	*player_angle = -atan2f(game->player.dir.x, game->player.dir.y) + M_PI;
}

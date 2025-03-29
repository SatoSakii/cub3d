/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:22:35 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/29 20:32:35 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_pixel(t_game *game, int index)
{
	return (index >= 0 && index < WINDOW_WIDTH * WINDOW_HEIGHT
		&& game->scene[index].rgba == 0x000000FF);
}

void	process_pixel(t_game *game, int index, bool flag)
{
	if (!is_valid_pixel(game, index))
		return ;
	if (flag)
		game->scene[index].rgba = 0x555C54FF;
	else
		game->scene[index].rgba = 0xF6F6DAFF;
}

void	init_minimap_position(t_game *game, int pos, t_ivec2d *map)
{
	if (pos & 0b1000)
		map->y = OFFSET;
	else
		map->y = WINDOW_HEIGHT - ((game->map.height * SQUARE_SIZE)
				- MINIMAP_R) - OFFSET;
	if (pos & 0b0010)
		map->x = OFFSET;
	else
		map->x = WINDOW_WIDTH - ((game->map.width * SQUARE_SIZE)
				- MINIMAP_R) + OFFSET;
}

void	rotate_point(t_dvec2d *m, float cx, float cy, t_theta theta)
{
	float	dx;
	float	dy;

	dx = m->x - cx;
	dy = m->y - cy;
	m->x = cx + (dx * theta.cos_theta - dy * theta.sin_theta);
	m->y = cy + (dx * theta.sin_theta + dy * theta.cos_theta);
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

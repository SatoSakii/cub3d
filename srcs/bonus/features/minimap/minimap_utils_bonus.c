/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 23:12:14 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:26:57 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_valid_pixel(t_game *game, int index)
{
	return (index >= 0 && index < WINDOW_WIDTH * WINDOW_HEIGHT
		&& game->scene[index].rgba == 0x000000FF);
}

void	process_pixel(t_game *game, int index, char tile)
{
	if (!is_valid_pixel(game, index))
		return ;
	if (tile == ' ')
		game->scene[index].rgba = 0x000000FF;
	else if (tile == '1' || tile == '2')
		game->scene[index].rgba = 0x555C54FF;
	else if (tile == 'C')
		game->scene[index].rgba = 0xFF3300FF;
	else if (tile == 'O')
		game->scene[index].rgba = 0x00FF33FF;
	else if (tile == '0')
		game->scene[index].rgba = 0xF6F6DAFF;
}

void	init_minimap_position(t_game *game, int pos, t_ivec2d *map)
{
	if (pos & 0b1000)
		map->y = MINIMAP_OFFSET;
	else
		map->y = WINDOW_HEIGHT - ((game->map.height * MINIMAP_SQUARE_SIZE)
				- MINIMAP_RADIUS) - MINIMAP_OFFSET;
	if (pos & 0b0010)
		map->x = MINIMAP_OFFSET;
	else
		map->x = WINDOW_WIDTH - ((game->map.width * MINIMAP_SQUARE_SIZE)
				- MINIMAP_RADIUS) + MINIMAP_OFFSET;
}

void	rotate_point(t_dvec2d *m, float cx, float cy, t_fvec2d theta)
{
	float	dx;
	float	dy;

	dx = m->x - cx;
	dy = m->y - cy;
	m->x = cx + (dx * theta.x - dy * theta.y);
	m->y = cy + (dx * theta.y + dy * theta.x);
}

void	draw_minimap_background(t_game *game, int minimap_x, int minimap_y)
{
	t_ivec2d	d;
	int			index;

	d.y = -MINIMAP_RADIUS;
	while (d.y <= MINIMAP_RADIUS)
	{
		d.x = -MINIMAP_RADIUS;
		while (d.x <= MINIMAP_RADIUS)
		{
			if (d.x * d.x + d.y * d.y <= MINIMAP_RADIUS * MINIMAP_RADIUS)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:14:45 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/29 06:13:46 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "cub3d.h"

#define SQUARE_SIZE 10
#define MINIMAP_R 100
#define OFFSET 20

static void	draw_square(t_game *game, t_dvec2d m, bool flag, t_theta theta)
{
	t_minimap	mini;

	ft_memset(&mini, 0, sizeof(mini));
	mini.m = m;
	printf("mini.m.x = %f | mini.m.y = %f\n", m.x, m.y);
	while (mini.tmp.x < SQUARE_SIZE)
	{
		draw_square_line(game, mini, flag, theta);
		mini.tmp.x++;
		mini.x.x += theta.cos_theta;
		mini.x.y += theta.sin_theta;
	}
}

static void	draw_player(t_game *game, int map_x, int map_y)
{
	int			radius;
	int			index;
	t_dvec2d	player;
	t_ivec2d	d;

	player.x = map_x + MINIMAP_R;
	player.y = map_y + MINIMAP_R;
	radius = SQUARE_SIZE / 4;
	d.x = -radius;
	while (d.x <= radius)
	{
		d.y = -radius;
		while (d.y <= radius)
		{
			if (d.x * d.x + d.y * d.y <= radius * radius)
			{
				index = ((player.y + d.y)) * WINDOW_WIDTH + ((player.x + d.x));
				if (index >= 0 && index < WINDOW_WIDTH * WINDOW_HEIGHT)
					game->scene[index].rgba = 0xFCBA03FF;
			}
			d.y++;
		}
		d.x++;
	}
}

void	init_map_pos(t_game *game, t_ivec2d *map, int pos)
{
	if (pos & 0b1000)
		map->y = OFFSET;
	else
		map->y = WINDOW_HEIGHT - ((game->map.height
					* SQUARE_SIZE) - MINIMAP_R) - OFFSET;
	if (pos & 0b0010)
		map->x = OFFSET;
	else
		map->x = WINDOW_WIDTH - ((game->map.width
					* SQUARE_SIZE) - MINIMAP_R) + OFFSET;
}

static bool	is_inside_minimap(t_dvec2d m, t_ivec2d map)
{
	int	dx;
	int	dy;

	dx = m.x - (map.x + MINIMAP_R);
	dy = m.y - (map.y + MINIMAP_R);
	return (dx * dx + dy * dy < MINIMAP_R * MINIMAP_R);
}

static void	draw_minimap_elements(t_game *game, t_ivec2d origin, t_ivec2d map,
			float player_angle, t_theta theta)
{
	t_dvec2d	m;
	size_t		y;
	size_t		x;
	bool		is_wall;

	y = 0;
	while (y < (size_t)game->map.height)
	{
		x = 0;
		while (x < (size_t)game->map.width)
		{
			m.x = x * SQUARE_SIZE + map.x - origin.x;
			m.y = y * SQUARE_SIZE + map.y - origin.y;
			rotate_point(&m, map.x + MINIMAP_R, map.y
				+ MINIMAP_R, player_angle);
			if (is_inside_minimap(m, map))
			{
				is_wall = (game->map.grid[y][x] == '1');
				draw_square(game, m, is_wall, theta);
			}
			x++;
		}
		y++;
	}
}

void	print_minimap(t_game *game, int pos)
{
	t_ivec2d	origin;
	t_ivec2d	map;
	t_theta		theta;
	float		player_angle;

	init_minimap(game, &origin, &map, &player_angle, pos);
	draw_minimap_background(game, map.x + MINIMAP_R, map.y + MINIMAP_R);
	theta.cos_theta = cos(-player_angle);
	theta.sin_theta = sin(-player_angle);
	draw_minimap_elements(game, origin, map, player_angle, theta);
	draw_player(game, map.x, map.y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:03:42 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/29 20:37:50 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft_maths.h"

static void	draw_square_inner(t_game *game, t_minimap minimap, t_dvec2d xd)
{
	t_dvec2d	yd;
	int			tmp_y;
	int			index;
	size_t		px;
	size_t		py;

	tmp_y = 0;
	yd = (t_dvec2d){0};
	while (tmp_y < SQUARE_SIZE)
	{
		px = (minimap.m.x + xd.x - yd.x);
		py = (minimap.m.y + xd.y + yd.y);
		index = py * WINDOW_WIDTH + px;
		process_pixel(game, index, minimap.flag);
		tmp_y++;
		yd.x += minimap.theta.sin_theta;
		yd.y += minimap.theta.cos_theta;
	}
}

static void	draw_square(t_game *game, t_dvec2d m, bool flag, t_theta theta)
{
	int			tmp_x;
	t_dvec2d	xd;
	t_minimap	minimap;

	xd = (t_dvec2d){0};
	minimap.m = m;
	minimap.theta = theta;
	minimap.flag = flag;
	tmp_x = 0;
	while (tmp_x < SQUARE_SIZE)
	{
		draw_square_inner(game, minimap, xd);
		tmp_x++;
		xd.x += theta.cos_theta;
		xd.y += theta.sin_theta;
	}
}

static void	draw_player(t_game *game, int map_x, int map_y)
{
	t_dvec2d	player;
	t_ivec2d	d;
	int			radius;
	int			index;

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
					game->scene[index].rgba = 0xFF00FFFF;
			}
			d.y++;
		}
		d.x++;
	}
}

static void	draw_minimap_elements(t_game *game, t_ivec2d map,
				t_ivec2d origin, t_theta theta)
{
	t_dvec2d	m;
	t_ivec2d	incr;
	bool		is_wall;

	incr.y = 0;
	while (incr.y < game->map.height)
	{
		incr.x = 0;
		while (incr.x < game->map.width - 1)
		{
			m.x = incr.x * SQUARE_SIZE + map.x - origin.x;
			m.y = incr.y * SQUARE_SIZE + map.y - origin.y;
			rotate_point(&m, map.x + MINIMAP_R, map.y + MINIMAP_R, theta);
			if ((m.x - (map.x + MINIMAP_R)) * (m.x - (map.x + MINIMAP_R))
				+ (m.y - (map.y + MINIMAP_R)) * (m.y - (map.y + MINIMAP_R))
				<= MINIMAP_R * MINIMAP_R)
			{
				is_wall = (game->map.grid[incr.y][incr.x] == '1');
				draw_square(game, m, is_wall, theta);
			}
			incr.x++;
		}
		incr.y++;
	}
}

void	print_minimap(t_game *game, int pos)
{
	t_ivec2d	origin;
	t_ivec2d	map;
	t_theta		theta;
	float		player_angle;

	origin.x = game->player.pos.x * SQUARE_SIZE - MINIMAP_R;
	origin.y = game->player.pos.y * SQUARE_SIZE - MINIMAP_R;
	init_minimap_position(game, pos, &map);
	draw_minimap_background(game, map.x + MINIMAP_R, map.y + MINIMAP_R);
	player_angle = -atan2f(game->player.dir.x, game->player.dir.y) + M_PI;
	theta.cos_theta = cos(-player_angle);
	theta.sin_theta = sin(-player_angle);
	draw_minimap_elements(game, map, origin, theta);
	draw_player(game, map.x, map.y);
}

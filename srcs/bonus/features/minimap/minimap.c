/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 23:12:14 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 23:30:08 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square_inner(t_game *game, t_minimap minimap, t_dvec2d xd)
{
	t_dvec2d	yd;
	int			tmp_y;
	int			index;
	size_t		px;
	size_t		py;

	tmp_y = 0;
	yd = (t_dvec2d){0};
	while (tmp_y < MINIMAP_SQUARE_SIZE)
	{
		px = (minimap.m.x + xd.x - yd.x);
		py = (minimap.m.y + xd.y + yd.y);
		index = py * WINDOW_WIDTH + px;
		process_pixel(game, index, minimap.flag);
		tmp_y++;
		yd.x += minimap.theta.y;
		yd.y += minimap.theta.x;
	}
}

static void	draw_square(t_game *game, t_dvec2d m, bool flag, t_fvec2d theta)
{
	int			tmp_x;
	t_dvec2d	xd;
	t_minimap	minimap;

	xd = (t_dvec2d){0};
	minimap.m = m;
	minimap.theta = theta;
	minimap.flag = flag;
	tmp_x = 0;
	while (tmp_x < MINIMAP_SQUARE_SIZE)
	{
		draw_square_inner(game, minimap, xd);
		tmp_x++;
		xd.x += theta.x;
		xd.y += theta.y;
	}
}

static void	draw_player(t_game *game, int map_x, int map_y)
{
	t_dvec2d	player;
	t_ivec2d	d;
	int			radius;
	int			index;

	player.x = map_x + MINIMAP_RADIUS;
	player.y = map_y + MINIMAP_RADIUS;
	radius = MINIMAP_SQUARE_SIZE / 4;
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
				t_ivec2d origin, t_fvec2d theta)
{
	const int	mini_r = MINIMAP_RADIUS;
	t_dvec2d	m;
	t_ivec2d	incr;

	incr.y = 0;
	while (incr.y < game->map.height)
	{
		incr.x = 0;
		while (incr.x < game->map.width - 1)
		{
			m.x = incr.x * MINIMAP_SQUARE_SIZE + map.x - origin.x;
			m.y = incr.y * MINIMAP_SQUARE_SIZE + map.y - origin.y;
			rotate_point(&m, map.x + mini_r, map.y + mini_r, theta);
			if ((m.x - (map.x + mini_r)) * (m.x - (map.x + mini_r))
				+ (m.y - (map.y + mini_r)) * (m.y - (map.y + mini_r))
				<= mini_r * mini_r)
			{
				if (incr.x <= (int)ft_strlen(game->map.grid[incr.y]))
					draw_square(game, m, (game->map.grid[incr.y]
						[incr.x] == '1'), theta);
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
	t_fvec2d	theta;
	float		player_angle;

	origin.x = game->player.pos.x * MINIMAP_SQUARE_SIZE - MINIMAP_RADIUS;
	origin.y = game->player.pos.y * MINIMAP_SQUARE_SIZE - MINIMAP_RADIUS;
	init_minimap_position(game, pos, &map);
	draw_minimap_background(game, map.x + MINIMAP_RADIUS,
		map.y + MINIMAP_RADIUS);
	player_angle = -atan2f(game->player.dir.x, game->player.dir.y) + M_PI;
	theta.x = cos(-player_angle);
	theta.y = sin(-player_angle);
	draw_minimap_elements(game, map, origin, theta);
	draw_player(game, map.x, map.y);
}

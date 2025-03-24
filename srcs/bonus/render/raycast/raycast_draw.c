/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:54:59 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 15:30:22 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_line(t_game *game, mlx_color *scene,
	int draws[2], t_render rdr)
{
	t_ivec2d	tex;
	double		step;
	double		tex_pos;
	t_textures	tx;

	tx = init_draw(draws, rdr.side, game);
	calculate_texture_coordinates(rdr.wall_x, &tx, rdr.side, &tex);
	step = (double)tx.height / (double)(rdr.line_height);
	tex_pos = ((draws[0] + 1) - game->player.dir.z - (WINDOW_HEIGHT >> 1)
			+ (rdr.line_height >> 1)) * step;
	while (++draws[0] <= draws[1])
	{
		tex.y = (int)tex_pos;
		tex_pos += step;
		if (tex.x >= 0 && tex.x < tx.width && tex.y >= 0 && tex.y < tx.height)
		{
			scene[draws[0] * WINDOW_WIDTH + rdr.x].rgba
				= tx.pixels[tex.y * tx.width + tex.x].rgba;
		}
	}
}

void	finish_raycast(t_ray *ray, t_game *game,
	mlx_color *scene, int side_x[2])
{
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;

	if (side_x[0] == EAST || side_x[0] == WEST)
		ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
	line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	draw_start = ((-line_height >> 1) + (WINDOW_HEIGHT >> 1))
		+ (int)game->player.dir.z;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = draw_start + line_height;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	if (side_x[0] == EAST || side_x[0] == WEST)
		wall_x = game->player.pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		wall_x = game->player.pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	wall_x -= floor(wall_x);
	draw_vertical_line(game, scene, (int [2]){draw_start, draw_end},
		(t_render){side_x[1], line_height, wall_x, side_x[0]});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 01:49:49 by albernar          #+#    #+#             */
/*   Updated: 2025/03/13 17:32:01 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_rays(t_ray *ray, t_game *game, int x, double inv_width)
{
	ray->camera_x = x * inv_width - 1.0;
	ray->raydir.x = game->player.dir.x + game->player.plane.x * ray->camera_x;
	ray->raydir.y = game->player.dir.y + game->player.plane.y * ray->camera_x;
	ray->map.x = (int)floor(game->player.pos.x);
	ray->map.y = (int)floor(game->player.pos.y);
	if (ray->raydir.x == 0.0)
		ray->deltadist.x = 1e30;
	else
		ray->deltadist.x = fabs(1.0 / ray->raydir.x);
	if (ray->raydir.y == 0.0)
		ray->deltadist.y = 1e30;
	else
		ray->deltadist.y = fabs(1.0 / ray->raydir.y);
}

void	perform_dda(t_ray *ray, t_game *game)
{
	if (ray->raydir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (game->player.pos.x - ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - game->player.pos.x)
			* ray->deltadist.x;
	}
	if (ray->raydir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (game->player.pos.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->map.y + 1.0 - game->player.pos.y)
			* ray->deltadist.y;
	}
}

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
	tex_pos = ((draws[0] + 1) - game->camera_pitch - WINDOW_HEIGHT / 2
			+ rdr.line_height / 2) * step;
	while (++draws[0] <= draws[1])
	{
		tex.y = (int)tex_pos;
		tex_pos += step;
		if (tex.x >= 0 && tex.x < tx.width && tex.y >= 0 && tex.y < tx.height)
		{
			if (rdr.inside_wall)
				scene[draws[0] * WINDOW_WIDTH + rdr.x].rgba
					= (tx.pixels[tex.y * tx.width + tex.x].rgba >> 1)
					& 0x7F7F7F7F;
			else
				scene[draws[0] * WINDOW_WIDTH + rdr.x].rgba
					= tx.pixels[tex.y * tx.width + tex.x].rgba;
		}
	}
}

static void	finish_raycast(t_ray *ray, t_game *game,
	mlx_color *scene, int side_x[2])
{
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;

	if (side_x[0] == EAST || side_x[0] == WEST)
		ray->perpwalldist = (ray->sidedist.x - ray->deltadist.x);
	else
		ray->perpwalldist = (ray->sidedist.y - ray->deltadist.y);
	line_height = (int)(WINDOW_HEIGHT / ray->perpwalldist);
	draw_start = (-line_height / 2 + WINDOW_HEIGHT / 2) + game->camera_pitch;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (line_height / 2 + WINDOW_HEIGHT / 2) + game->camera_pitch;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	if (side_x[0] == EAST || side_x[0] == WEST)
		wall_x = game->player.pos.y + ray->perpwalldist * ray->raydir.y;
	else
		wall_x = game->player.pos.x + ray->perpwalldist * ray->raydir.x;
	wall_x -= floor(wall_x);
	draw_vertical_line(game, scene, (int [2]){draw_start, draw_end},
		(t_render){side_x[1], line_height, wall_x, side_x[0],
		ray->inside_wall});
}

void	raycast(t_game *game)
{
	t_ray		ray;
	double		inv_width;
	int			x;
	int			side;
	mlx_color	*scene;

	scene = game->scene;
	inv_width = 2.0 / (double)WINDOW_WIDTH;
	x = 0;
	fill_background(scene, game);
	while (x < WINDOW_WIDTH)
	{
		init_rays(&ray, game, x, inv_width);
		perform_dda(&ray, game);
		ray.hit = false;
		check_hit(&ray, game, &side);
		if (ray.hit)
			finish_raycast(&ray, game, scene, (int [2]){side, x});
		x++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:36:10 by albernar          #+#    #+#             */
/*   Updated: 2025/03/28 22:36:36 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_dda(t_ray *ray, t_game *game)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - game->player.pos.y)
			* ray->delta_dist.y;
	}
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

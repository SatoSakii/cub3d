/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:20:15 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/28 20:15:34 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_yet_another_rays(t_game *game, t_ray *ray)
{
	ray->ray_dir.x = game->player.dir.x;
	ray->ray_dir.y = game->player.dir.y;
	ray->map.x = (int)floor(game->player.pos.x);
	ray->map.y = (int)floor(game->player.pos.y);
	if (ray->ray_dir.x == 0.0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0.0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0 / ray->ray_dir.y);
}

void	raycast_door(t_game *game)
{
	t_ray	ray;
	int		side;
	double	wall_dist;
	char	tile;

	init_yet_another_rays(game, &ray);
	perform_dda(&ray, game);
	ray.hit = false;
	while (!ray.hit)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map.x += ray.step.x;
			side = EAST;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map.y += ray.step.y;
			side = NORTH;
		}
		if (ray.side_dist.y - ray.delta_dist.y > MAX_RAY_DIST)
			break ;
		if (ray.map.x >= 0 && ray.map.x < (int)game->map.width - 1
			&& ray.map.y >= 0 && ray.map.y < (int)game->map.height)
		{
			if (game->map.grid[ray.map.y][ray.map.x] == 'C'
				|| game->map.grid[ray.map.y][ray.map.x] == 'O')
			{
				game->is_door = game->map.grid[ray.map.y][ray.map.x];
				ray.hit = true;
			}
		}
	}
	if (ray.hit)
	{
		if (side == EAST || side == WEST)
			wall_dist = (ray.side_dist.x - ray.delta_dist.x);
		else
			wall_dist = (ray.side_dist.y - ray.delta_dist.y);
		if (wall_dist <= DELETE_WALL_DISTANCE && (ray.map.x >= 0
				&& ray.map.x < (int)game->map.width && ray.map.y >= 0
				&& ray.map.y < (int)game->map.height))
		{
			tile = game->map.grid[ray.map.y][ray.map.x];
			if (tile == 'C' || tile == 'O')
				game->map.grid[ray.map.y][ray.map.x] = tile ^ 0x0C;
		}
	}
}

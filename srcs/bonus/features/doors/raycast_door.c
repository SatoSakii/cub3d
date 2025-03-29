/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 03:48:54 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 04:13:24 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_hit_door(t_game *game, t_ray *ray)
{
	char		tile;

	if (ray->map.x >= 0 && ray->map.x < (int)game->map.width - 1
		&& ray->map.y >= 0 && ray->map.y < (int)game->map.height)
	{
		tile = game->map.grid[ray->map.y][ray->map.x];
		if (tile == 'C' || tile == 'O')
		{
			game->features.is_door = tile;
			ray->hit = true;
		}
	}
}

static void	raycast_door(t_game *game, t_ray *ray, int *side)
{
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			*side = EAST;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			*side = NORTH;
		}
		if (ray->side_dist.y - ray->delta_dist.y > MAX_RAY_DIST)
			break ;
		check_hit_door(game, ray);
	}
}

void	open_door(t_game *game)
{
	t_ray		ray;
	int			side;
	double		door_dist;
	char		tile;

	init_ray_custom(game, &ray);
	perform_dda(&ray, game);
	ray.hit = false;
	raycast_door(game, &ray, &side);
	if (ray.hit)
	{
		if (side == EAST)
			door_dist = ray.side_dist.x - ray.delta_dist.x;
		else
			door_dist = ray.side_dist.y - ray.delta_dist.y;
		if (door_dist < INTERACT_DOOR_DISTANCE && (ray.map.x >= 0
				&& ray.map.x < (int)game->map.width && ray.map.y >= 0
				&& ray.map.y < (int)game->map.height))
		{
			tile = game->map.grid[ray.map.y][ray.map.x];
			if (tile == 'C' || tile == 'O')
				game->map.grid[ray.map.y][ray.map.x] = tile ^ 0x0C;
		}
	}
}

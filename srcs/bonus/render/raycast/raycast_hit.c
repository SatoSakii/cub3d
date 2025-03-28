/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:52:44 by albernar          #+#    #+#             */
/*   Updated: 2025/03/28 20:17:49 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_wall_side(int *side, t_ray *ray, int _side)
{
	if (_side)
	{
		if (ray->step.x < 0)
			*side = WEST;
		else
			*side = EAST;
	}
	else
	{
		if (ray->step.y < 0)
			*side = NORTH;
		else
			*side = SOUTH;
	}
}

void	check_hit(t_ray *ray, t_game *game, int *side)
{
	int		is_x_side;

	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			is_x_side = 1;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			is_x_side = 0;
		}
		set_wall_side(side, ray, is_x_side);
		if (ray->side_dist.y - ray->delta_dist.y > MAX_RAY_DIST)
			break ;
		if (ray->map.x >= 0 && ray->map.x < (int)game->map.width - 1
			&& ray->map.y >= 0 && ray->map.y < (int)game->map.height)
		{
			if (game->map.grid[ray->map.y][ray->map.x] == '1')
				ray->hit = true;
			else if (game->map.grid[ray->map.y][ray->map.x] == 'C')
			{
				game->is_door = 'C';
				ray->hit = true;
			}
		}
	}
}

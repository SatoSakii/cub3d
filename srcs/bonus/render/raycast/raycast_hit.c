/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:52:44 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 22:58:34 by albernar         ###   ########.fr       */
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

static void	check_hit_validity(t_ray *ray, t_game *game)
{
	if (ray->map.x >= 0 && ray->map.x < (int)game->map.width - 1
		&& ray->map.y >= 0 && ray->map.y < (int)game->map.height
		&& ray->map.x < (int)ft_strlen(game->map.grid[ray->map.y]) - 1
		&& game->map.grid[ray->map.y][ray->map.x] != ' ')
	{
		if (game->map.grid[ray->map.y][ray->map.x] == '1')
			ray->hit = true;
		if (game->map.grid[ray->map.y][ray->map.x] == 'C')
		{
			game->features.is_door = 'C';
			ray->hit = true;
		}
		if (game->map.grid[ray->map.y][ray->map.x] == '2')
		{
			game->features.wall_sprite = true;
			ray->hit = true;
		}
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
		check_hit_validity(ray, game);
	}
}

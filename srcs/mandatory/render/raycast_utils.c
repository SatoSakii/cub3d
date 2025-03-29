/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:36:32 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 22:55:09 by albernar         ###   ########.fr       */
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

bool	is_insidewall(t_game *game)
{
	t_ivec2d	pos;

	pos = (t_ivec2d){(int)floor(game->player.pos.x),
		(int)floor(game->player.pos.y)};
	return (game->player.pos.x >= 0
		&& game->player.pos.x < game->map.width
		&& game->player.pos.y >= 0 && game->player.pos.y < game->map.height
		&& pos.x < (int)ft_strlen(game->map.grid[pos.y])
		&& game->map.grid[pos.y][pos.x] == '1');
}

static void	invert_side(int *side)
{
	if (*side == NORTH)
		*side = SOUTH;
	else if (*side == SOUTH)
		*side = NORTH;
	else if (*side == EAST)
		*side = WEST;
	else if (*side == WEST)
		*side = EAST;
}

static int	check_state(t_ray *ray, bool inside_wall, t_game *game, int *side)
{
	if (!inside_wall && (ray->sidedist.y - ray->deltadist.y) > MAX_RAY_DIST)
		return (2);
	else if (ray->map.x >= 0 && ray->map.x < (int)game->map.width - 1
		&& ray->map.y >= 0 && ray->map.y < (int)game->map.height
		&& ray->map.x < (int)ft_strlen(game->map.grid[ray->map.y]) - 1
		&& game->map.grid[ray->map.y][ray->map.x] != ' ')
	{
		if (inside_wall)
		{
			if (game->map.grid[ray->map.y][ray->map.x] == '0')
			{
				ray->hit = true;
				invert_side(side);
			}
		}
		else if (game->map.grid[ray->map.y][ray->map.x] == '1')
			ray->hit = true;
	}
	else if (inside_wall)
	{
		ray->hit = true;
		invert_side(side);
	}
	return (0);
}

void	check_hit(t_ray *ray, t_game *game, int *side)
{
	int		is_x_side;

	ray->inside_wall = is_insidewall(game);
	while (!ray->hit)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			is_x_side = 1;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			is_x_side = 0;
		}
		set_wall_side(side, ray, is_x_side);
		if (check_state(ray, ray->inside_wall, game, side) == 2)
			break ;
	}
}

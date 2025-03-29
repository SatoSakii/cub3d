/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 04:28:16 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 04:33:36 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	save_wall(t_game *game, int x, int y)
{
	int	i;

	if (game->features.destroy_wall.index == MAX_SAVE_WALLS)
	{
		i = -1;
		while (++i < MAX_SAVE_WALLS - 1)
			game->features.destroy_wall.pos[i]
				= game->features.destroy_wall.pos[i + 1];
		game->features.destroy_wall.pos[MAX_SAVE_WALLS - 1].x = x;
		game->features.destroy_wall.pos[MAX_SAVE_WALLS - 1].y = y;
	}
	else
	{
		game->features.destroy_wall.pos[game->features.destroy_wall.index].x
			= x;
		game->features.destroy_wall.pos[game->features.destroy_wall.index].y
			= y;
		game->features.destroy_wall.index++;
	}
}

void	restore_wall(t_game *game)
{
	int	x;
	int	y;

	if (game->features.destroy_wall.index == 0)
		return ;
	game->features.destroy_wall.index--;
	x = game->features.destroy_wall.pos[game->features.destroy_wall.index].x;
	y = game->features.destroy_wall.pos[game->features.destroy_wall.index].y;
	game->map.grid[y][x] = '1';
}

void	destroy_wall(t_game *game)
{
	t_ray	ray;
	int		side;
	double	wall_dist;

	init_ray_custom(game, &ray);
	perform_dda(&ray, game);
	ray.hit = false;
	check_hit(&ray, game, &side);
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
			if (game->map.grid[ray.map.y][ray.map.x] == '1')
			{
				save_wall(game, ray.map.x, ray.map.y);
				game->map.grid[ray.map.y][ray.map.x] = '0';
			}
		}
	}
}

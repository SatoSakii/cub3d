/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:14:39 by albernar          #+#    #+#             */
/*   Updated: 2025/03/19 19:04:17 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	save_wall(t_game *game, int x, int y)
{
	int	i;

	if (game->wall_save.index == MAX_SAVE_WALL)
	{
		i = -1;
		while (++i < MAX_SAVE_WALL - 1)
			game->wall_save.save[i] = game->wall_save.save[i + 1];
		game->wall_save.save[MAX_SAVE_WALL - 1].x = x;
		game->wall_save.save[MAX_SAVE_WALL - 1].y = y;
	}
	else
	{
		game->wall_save.save[game->wall_save.index].x = x;
		game->wall_save.save[game->wall_save.index].y = y;
		game->wall_save.index++;
	}
}

static void	init_destroy_wall(t_game *game, t_ray *ray)
{
	ray->raydir.x = game->player.dir.x;
	ray->raydir.y = game->player.dir.y;
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

void	restore_wall(t_game *game)
{
	int	x;
	int	y;

	if (game->wall_save.index == 0)
		return ;
	game->wall_save.index--;
	x = game->wall_save.save[game->wall_save.index].x;
	y = game->wall_save.save[game->wall_save.index].y;
	game->map.grid[y][x] = '1';
}

void	destroy_wall(t_game *game)
{
	t_ray	ray;
	int		side;
	double	wall_dist;

	init_destroy_wall(game, &ray);
	perform_dda(&ray, game);
	ray.hit = false;
	check_hit(&ray, game, &side);
	if (ray.hit)
	{
		if (side == EAST || side == WEST)
			wall_dist = (ray.sidedist.x - ray.deltadist.x);
		else
			wall_dist = (ray.sidedist.y - ray.deltadist.y);
		if (wall_dist <= DELETE_WALL_DIST && (ray.map.x >= 0
				&& ray.map.x < (int)game->map.width && ray.map.y >= 0
				&& ray.map.y < (int)game->map.height))
		{
			if (game->map.grid[ray.map.y][ray.map.x] == '1')
			{
				save_wall(game, ray.map.x, ray.map.y);
				game->map.grid[ray.map.y][ray.map.x] = '0';
				game->packet.wx = ray.map.x;
				game->packet.wy = ray.map.y;
			}
		}
	}
}

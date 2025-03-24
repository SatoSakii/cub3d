/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:36:26 by albernar          #+#    #+#             */
/*   Updated: 2025/03/21 21:23:07 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rays(t_ray *ray, t_game *game, int x, double inv_width)
{
	ray->camera_x = x * inv_width - 1.0;
	ray->ray_dir.x = game->player.dir.x + game->player.plane.x * ray->camera_x;
	ray->ray_dir.y = game->player.dir.y + game->player.plane.y * ray->camera_x;
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

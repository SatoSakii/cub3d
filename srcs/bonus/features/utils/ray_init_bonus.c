/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 03:45:49 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:26:59 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_ray_custom(t_game *game, t_ray *ray)
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

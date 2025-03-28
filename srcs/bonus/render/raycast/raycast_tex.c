/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:57:26 by albernar          #+#    #+#             */
/*   Updated: 2025/03/28 16:18:50 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_textures	init_draw(int draws[2], int side, t_game *game)
{
	if (draws[0] < 0)
		draws[0] = 0;
	if (draws[1] >= WINDOW_HEIGHT)
		draws[1] = WINDOW_HEIGHT - 1;
	draws[0] -= 1;
	if (game->is_door == 'C')
		return (game->door);
	else if (side == NORTH)
		return (game->no);
	else if (side == SOUTH)
		return (game->so);
	else if (side == WEST)
		return (game->we);
	else
		return (game->ea);
}

void	calculate_texture_coordinates(double wall_x, t_textures *texture,
	int side, t_ivec2d *tex)
{
	tex->x = (int)(wall_x * (double)texture->width);
	if ((side == EAST && tex->x > 0)
		|| (side == WEST && tex->x < texture->width - 1))
		tex->x = texture->width - tex->x - 1;
	if ((side == SOUTH && tex->x > 0)
		|| (side == NORTH && tex->x < texture->width - 1))
		tex->x = texture->width - tex->x - 1;
	if (tex->x < 0)
		tex->x = 0;
	if (tex->x >= texture->width)
		tex->x = texture->width - 1;
}

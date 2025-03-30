/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:57:26 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:40:49 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_textures	is_sprite(t_game *game, int frames)
{
	if (frames >= STEP_PER_UPDATE_WALL
		&& frames <= STEP_PER_UPDATE_WALL * 2)
		return (game->sprites[0]);
	if (frames > STEP_PER_UPDATE_WALL * 2
		&& frames <= STEP_PER_UPDATE_WALL * 3)
		return (game->sprites[1]);
	return (game->sprites[2]);
}

t_textures	init_draw(int draws[2], int side, t_game *game)
{
	static int	frames = 0;

	if (draws[0] < 0)
		draws[0] = 0;
	if (draws[1] >= WINDOW_HEIGHT)
		draws[1] = WINDOW_HEIGHT - 1;
	draws[0] -= 1;
	frames++;
	if (frames > STEP_PER_UPDATE_WALL * 4)
		frames = 0;
	if (game->features.is_door == 'C')
		return (game->door);
	if (game->features.wall_sprite)
		return (is_sprite(game, frames));
	if (side == NORTH)
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
	if ((side == SOUTH && tex->x > 0)
		|| (side == WEST && tex->x < texture->width - 1))
		tex->x = texture->width - tex->x - 1;
	if (tex->x < 0)
		tex->x = 0;
	if (tex->x >= texture->width)
		tex->x = texture->width - 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:32:30 by albernar          #+#    #+#             */
/*   Updated: 2025/03/11 14:43:54 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_background(mlx_color *scene, t_game *game)
{
	int				horizon;
	bool			inside_wall;
	unsigned int	ceiling_color;
	unsigned int	floor_color;

	inside_wall = is_insidewall(game);
	ceiling_color = game->ceiling.color;
	floor_color = game->floor.color;
	if (inside_wall)
	{
		ceiling_color = (ceiling_color >> 1) & 0x7F7F7F7F;
		floor_color = (floor_color >> 1) & 0x7F7F7F7F;
	}
	horizon = (WINDOW_HEIGHT / 2) + (int)game->camera_pitch;
	if (horizon < 0)
		horizon = 0;
	if (horizon > WINDOW_HEIGHT)
		horizon = WINDOW_HEIGHT;
	mlxcolor_memset(scene, ceiling_color,
		horizon * WINDOW_WIDTH * sizeof(mlx_color));
	mlxcolor_memset(scene + (horizon * WINDOW_WIDTH), floor_color,
		(WINDOW_HEIGHT - horizon) * WINDOW_WIDTH * sizeof(mlx_color));
}

t_textures	init_draw(int draws[2], int side, t_game *game)
{
	if (draws[0] < 0)
		draws[0] = 0;
	if (draws[1] >= WINDOW_HEIGHT)
		draws[1] = WINDOW_HEIGHT - 1;
	draws[0] -= 1;
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

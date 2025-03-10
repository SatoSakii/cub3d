/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:32:30 by albernar          #+#    #+#             */
/*   Updated: 2025/03/10 13:08:16 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_background(mlx_color *scene, t_game *game)
{
	int	pos;
	int	half_pixels;
	int	total_pixels;

	total_pixels = WINDOW_WIDTH * WINDOW_HEIGHT;
	half_pixels = WINDOW_WIDTH * (WINDOW_HEIGHT / 2);
	pos = 0;
	while (pos < half_pixels)
	{
		scene[pos].rgba = game->ceiling.color;
		pos++;
	}
	while (pos < total_pixels)
	{
		scene[pos].rgba = game->floor.color;
		pos++;
	}
}

void	change_background(bool inside_wall, t_game *game)
{
	if (inside_wall)
	{
		game->ceiling.color = (game->ceiling.color_bak >> 1) & 0x7F7F7F7F;
		game->floor.color = (game->floor.color_bak >> 1) & 0x7F7F7F7F;
	}
	else
	{
		game->ceiling.color = game->ceiling.color_bak;
		game->floor.color = game->floor.color_bak;
	}
}

unsigned int	darker_color(bool inside_wall, unsigned int color)
{
	if (inside_wall)
		color = (color >> 1) & 0x7F7F7F7F;
	return (color);
}

t_textures	get_texture_by_side(t_game *game, int side)
{
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:32:30 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 19:26:40 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_background(mlx_color *scene, t_game *game)
{
	int				half_pixels;
	int				total_pixels;
	bool			inside_wall;
	unsigned int	tmp;
	unsigned int	tmp2;

	total_pixels = WINDOW_WIDTH * WINDOW_HEIGHT;
	half_pixels = WINDOW_WIDTH * (WINDOW_HEIGHT >> 1);
	inside_wall = is_insidewall(game);
	tmp = game->ceiling.color;
	tmp2 = game->floor.color;
	if (inside_wall)
	{
		tmp = (tmp >> 1) & 0x7F7F7F7F;
		tmp2 = (tmp2 >> 1) & 0x7F7F7F7F;
	}
	mlxcolor_memset(scene, tmp,
		half_pixels * sizeof(mlx_color));
	mlxcolor_memset(scene + half_pixels, tmp2,
		(total_pixels - half_pixels) * sizeof(mlx_color));
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

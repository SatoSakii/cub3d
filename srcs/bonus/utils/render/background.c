/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:47:29 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 15:31:56 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_background(mlx_color *scene, t_game *game)
{
	int				horizon;
	unsigned int	ceiling_color;
	unsigned int	floor_color;

	ceiling_color = game->ceiling.color;
	floor_color = game->floor.color;
	horizon = ((WINDOW_HEIGHT >> 1)) + (int)game->player.dir.z;
	if (horizon < 0)
		horizon = 0;
	if (horizon > WINDOW_HEIGHT)
		horizon = WINDOW_HEIGHT;
	mlxcolor_memset(scene, ceiling_color,
		horizon * WINDOW_WIDTH * sizeof(mlx_color));
	mlxcolor_memset(scene + (horizon * WINDOW_WIDTH), floor_color,
		(WINDOW_HEIGHT - horizon) * WINDOW_WIDTH * sizeof(mlx_color));
}

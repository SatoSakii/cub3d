/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_mlxinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:32:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/25 20:55:16 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>

void	init_mlx(t_mlx *mlx)
{    
	mlx->mlx = mlx_init();

    mlx->info.title = "cub3D";
    mlx->info.width = WINDOW_WIDTH;
    mlx->info.height = WINDOW_HEIGHT;
    mlx->win = mlx_new_window(mlx->mlx, &mlx->info);
}

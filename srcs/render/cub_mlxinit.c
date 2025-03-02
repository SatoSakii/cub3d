/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_mlxinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:32:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/02 12:43:02 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

void	init_mlx(t_mlx *mlx)
{    
	mlx->mlx = mlx_init();

    mlx->info.title = "cub3D";
    mlx->info.width = WINDOW_WIDTH;
    mlx->info.height = WINDOW_HEIGHT;
    mlx->win = mlx_new_window(mlx->mlx, &mlx->info);
}

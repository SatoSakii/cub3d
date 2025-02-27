/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:34:18 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/27 18:19:00 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#include "mlx.h"
#include "cub3d.h"

void	init_mlx(t_mlx *mlx);
void	cub_raycasting(t_game *game);

#endif

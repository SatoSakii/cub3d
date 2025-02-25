/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:34:18 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/25 20:55:51 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include "mlx.h"

typedef struct	s_mlx
{
	mlx_context				mlx;
	mlx_window_create_info	info;
	mlx_window				win;
}	t_mlx;

void	init_mlx(t_mlx *mlx);

#endif

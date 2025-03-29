/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feature.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:57:40 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 01:57:51 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURE_H
# define FEATURE_H

#include "libft_maths.h"
typedef struct s_destroy_wall
{
	t_ivec2d	pos[MAX_SAVE_WALLS];
	int			index;
}	t_destroy_wall;

typedef struct s_features
{
	t_destroy_wall	destroy_wall;
	bool			show_debug_menu;
	bool			unlock_cursor;
}	t_features;

typedef struct s_theta
{
	float	cos_theta;
	float	sin_theta;
}	t_theta;

typedef struct s_minimap
{
	t_dvec2d	m;
	t_ivec2d	x;
	t_ivec2d	tmp;
	t_ivec2d	origin;
	float		player_angle;
	t_ivec2d	map;
}	t_minimap;
#endif

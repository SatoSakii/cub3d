/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feature.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:57:40 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 20:34:16 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURE_H
# define FEATURE_H

# define SQUARE_SIZE 10
# define MINIMAP_R 100
# define OFFSET 20

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
	bool		flag;
	t_theta		theta;
}	t_minimap;

#endif

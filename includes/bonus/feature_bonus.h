/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feature_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:57:40 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:26:16 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURE_BONUS_H
# define FEATURE_BONUS_H

typedef struct s_destroy_wall
{
	t_ivec2d	pos[MAX_SAVE_WALLS];
	int			index;
}	t_destroy_wall;

typedef struct s_minimap
{
	t_dvec2d	m;
	t_fvec2d	theta;
	char		tile;
}	t_minimap;

typedef struct s_features
{
	t_destroy_wall	destroy_wall;
	char			is_door;
	bool			wall_sprite;
	bool			show_debug_menu;
	bool			unlock_cursor;
}	t_features;

#endif
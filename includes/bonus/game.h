/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:29:02 by albernar          #+#    #+#             */
/*   Updated: 2025/03/28 23:43:04 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

typedef struct s_player
{
	t_dvec3d	dir;
	t_dvec3d	pos;
	t_dvec2d	plane;
	t_dvec3d	direction;
	double		velocity;
	double		sensitivity;
	bool		is_running;
}	t_player;

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
}	t_map;

typedef struct s_game
{
	t_textures	no;
	t_textures	so;
	t_textures	we;
	t_textures	ea;
	t_colors	floor;
	t_colors	ceiling;
	t_player	player;
	t_map		map;
	t_mlx		mlx;
	t_controls	controls;
	mlx_color	*scene;
	t_features	features;
	t_main_menu	main_menu;
	t_player	other_player[MAX_PLAYERS - 1];
}	t_game;

#endif
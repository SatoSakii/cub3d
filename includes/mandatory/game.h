/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:09:35 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 17:19:32 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

typedef struct s_player
{
	t_dvec3d	dir;
	t_dvec3d	pos;
	t_dvec2d	plane;
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
	t_keys		keys;
	mlx_color	*scene;
}	t_game;

#endif
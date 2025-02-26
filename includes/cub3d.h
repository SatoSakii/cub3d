/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:47:13 by albernar          #+#    #+#             */
/*   Updated: 2025/02/25 20:18:32 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include "error.h"
# include "colors.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# define MAP_TILES "10"
# define MAP_DIRECTIONS "NSWE"

typedef struct s_textures
{
	int		width;
	int		height;
	char	*path;
	void	*addr; // addr of line from gnl(); to free
	void	*img; // img of mlx(); useless for parsing
}	t_textures;

typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
}	t_colors;

typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
}	t_player;

typedef struct s_map
{
	char	**grid; // manage all gnl(); lines : no strdup, no malloc
	int		grid_size;
}	t_map;

typedef struct s_game
{
	t_textures	no;
	t_textures	so;
	t_textures	ea;
	t_textures	we;
	t_colors	ceiling;
	t_colors	floor;
	t_player	player;
	t_map		map;
}	t_game;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

#endif

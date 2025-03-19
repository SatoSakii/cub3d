/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 01:01:25 by albernar          #+#    #+#             */
/*   Updated: 2025/03/19 19:17:15 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "dynamic_parser.h"
# include "error.h"
# include "colors.h"
#include "server.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <mlx.h>
# include <mlx_extended.h>
# include <SDL2/SDL_scancode.h>
# include <sys/time.h>
# include <math.h>
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MAX_PITCH 1080.0
# define MOVE_SPEED 4
# define ROTATE_SPEED 1
# define MAX_RAY_DIST 100.0
# define DELETE_WALL_DIST 1.5
# define OFFSET_SLIDE_WALL 0.1
# define MAX_SAVE_WALL 10
# define SPEED_FACTOR 4

typedef enum e_direction
{
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT
}	t_direction;

typedef enum e_rotation
{
	ROTATION_LEFT,
	ROTATION_RIGHT
}	t_rotation;

typedef enum e_walldir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_walldir;

typedef struct s_dvec2d
{
	double	x;
	double	y;
}	t_dvec2d;

typedef struct s_ivec2d
{
	int	x;
	int	y;
}	t_ivec2d;

typedef struct s_render
{
	int		x;
	int		line_height;
	double	wall_x;
	int		side;
	bool	inside_wall;
}	t_render;

typedef struct s_ray
{
	double		camera_x;
	double		perpwalldist;
	t_dvec2d	raydir;
	t_dvec2d	deltadist;
	t_dvec2d	sidedist;
	t_ivec2d	step;
	t_ivec2d	map;
	bool		hit;
	bool		inside_wall;
}	t_ray;

typedef struct s_player
{
	t_dvec2d	dir;
	t_dvec2d	pos;
	t_dvec2d	plane;
	bool		is_running;
}	t_player;

typedef struct s_map
{
	char	**grid;
	size_t	height;
	size_t	width;
}	t_map;

typedef struct s_textures
{
	int			width;
	int			height;
	char		*path;
	void		*addr;
	mlx_image	img;
	mlx_color	*pixels;
}	t_textures;

typedef struct s_mlx
{
	mlx_context				ctx;
	mlx_window_create_info	info;
	mlx_window				win;
}	t_mlx;

typedef struct s_colors
{
	int				r;
	int				g;
	int				b;
	unsigned int	color;
}	t_colors;

typedef struct s_keys
{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
}	t_keys;

typedef struct s_destroy_save
{
	t_ivec2d	save[MAX_SAVE_WALL];
	int			index;
}	t_destroy_save;

typedef struct s_game
{
	t_textures		no;
	t_textures		so;
	t_textures		ea;
	t_textures		we;
	t_textures		crosshair;
	t_colors		ceiling;
	t_colors		floor;
	t_player		player;
	t_map			map;
	t_keys			keys;
	t_mlx			mlx;
	bool			collision;
	double			camera_pitch;
	t_destroy_save	wall_save;
	mlx_color		*scene;
	t_server		server;
	int				client_socket;
	struct sockaddr_in	serv_addr;
	t_packet		packet;
}	t_game;

// Events Hooks
void			event_loop(void *param);
void			event_keydown(int keycode, void *param);
void			event_keyup(int keycode, void *param);

// Events Moves
void			rotate_player(t_game *game, t_player *player,
					double delta_time);
void			move_player(t_game *game,
					t_player *player, int direction, double delta_time);

// Render
void			raycast(t_game *game);
void			perform_dda(t_ray *ray, t_game *game);

// Raycast Utils
void			fill_background(mlx_color *scene, t_game *game);
void			calculate_texture_coordinates(double wall_x,
					t_textures *texture, int side, t_ivec2d *tex);
void			check_hit(t_ray *ray, t_game *game, int *side);
bool			is_insidewall(t_game *game);

// Utils
void			free_game(t_game *game);
void			init_game(t_game *game, t_error_ctx *ctx);
int				init_mlx(t_game *game, t_mlx *mlx);
int				init_textures(t_game *game, t_mlx *mlx);
double			get_delta_time(void);
void			print_fps(void);
t_textures		init_draw(int draws[2], int side, t_game *game);
void			*mlxcolor_memset(void *dest, uint32_t c, size_t n);
void			destroy_wall(t_game *game);
void			restore_wall(t_game *game);

#endif

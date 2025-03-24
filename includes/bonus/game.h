/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:29:02 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 17:16:16 by albernar         ###   ########.fr       */
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

bool		block_game(t_game *game);

void		free_game(t_game *game);
void		init_game(t_game *game, t_error_ctx *ctx);
int			init_mlx(t_game *game, t_mlx *mlx);
bool		block_game(t_game *game);

void		update_player(t_game *game, t_player *player, double delta_time);
void		update_velocity(t_player *player);
void		update_pos(t_game *game, t_player *player, t_dvec3d pos);
void		rotate_player(t_game *game, t_player *player, double delta_time);
void		move_player(t_player *player, t_direction dir);

void		event_keydown(int keycode, void *param);
void		event_keyup(int keycode, void *param);
void		event_window(int event, void *param);
void		event_mousedown(int button, void *param);
void		event_mouseup(int button, void *param);
void		event_loop(void *param);

double		get_delta_time(void);
void		print_fps(void);

t_textures	init_draw(int draws[2], int side, t_game *game);
void		calculate_texture_coordinates(double wall_x, t_textures *texture,
				int side, t_ivec2d *tex);
void		finish_raycast(t_ray *ray, t_game *game,
				mlx_color *scene, int side_x[2]);
void		check_hit(t_ray *ray, t_game *game, int *side);
void		init_rays(t_ray *ray, t_game *game, int x, double inv_width);
void		raycast(t_game *game);
void		fill_background(mlx_color *scene, t_game *game);
void		*mlxcolor_memset(void *dest, uint32_t c, size_t n);
void		perform_dda(t_ray *ray, t_game *game);

#endif
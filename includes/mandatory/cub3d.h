/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:09:06 by albernar          #+#    #+#             */
/*   Updated: 2025/03/25 03:37:10 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <SDL2/SDL.h>
# include <SDL2/SDL_scancode.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/time.h>
# include <mlx.h>
# include <mlx_extended.h>
# include <math.h>

# include "libft.h"
# include "colors.h"
# include "defines.h"
# include "dynamic_parser.h"
# include "parser.h"
# include "enums.h"
# include "render.h"
# include "controls.h"
# include "game.h"

// Events Hooks
void			event_loop(void *param);
void			event_keydown(int keycode, void *param);
void			event_keyup(int keycode, void *param);
void			event_window(int event, void *param);

// Events Moves
void			rotate_player(t_player *player, int rotation,
					double delta_time);
void			move_player(t_player *player, int direction,
					double delta_time);

// Render
void			raycast(t_game *game);

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

#endif
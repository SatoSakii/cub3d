/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:06:20 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 04:32:48 by albernar         ###   ########.fr       */
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
# include <vulkan/vulkan_core.h>
# include <mlx.h>
# include <mlx_extended.h>
# include <math.h>

# include "libft.h"
# include "colors.h"
# include "controls.h"
# include "defines.h"
# include "dynamic_parser.h"
# include "enums.h"
# include "parser.h"
# include "feature.h"
# include "third_party.h"
# include "render.h"
# include "game.h"
# include "loader.h"
# include "vulkan_manager.h"
# include "vk_render.h"

typedef enum s_tribool
{
	TRIBOOL_FALSE = 0,
	TRIBOOL_TRUE = 1,
	TRIBOOL_UNSET = -1
}	t_tribool;

t_tribool	block_game(t_game *game);
void		game_render(t_game *game, double delta_time, t_tribool block);

void		free_game(t_game *game);
void		init_game(t_game *game, t_error_ctx *ctx);
int			init_mlx(t_game *game, t_mlx *mlx);

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

void		setup_imgui_colors(ImGuiStyle *style);
void		setup_imgui_style(void);

void		draw_button(const char *text,
				float y_pos, t_fvec2d w_h, t_game *game);
void		draw_title(void);
void		draw_sliders(t_game *game);
void		settings_menu(t_game *game);
void		start_menu(t_game *game);
void		controls_menu(t_game *game);
void		draw_controls_buttons(const char *text, t_ivec2d pos,
				t_game *game, int i);
void		draw_debug_menu(t_game *game);
void		init_ray_custom(t_game *game, t_ray *ray);
void		open_door(t_game *game);
void		destroy_wall(t_game *game);
void		restore_wall(t_game *game);

#endif
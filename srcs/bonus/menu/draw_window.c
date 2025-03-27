/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 02:36:04 by albernar          #+#    #+#             */
/*   Updated: 2025/03/27 23:58:25 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_button(const char *text,
	float y_pos, t_fvec2d w_h, t_game *game)
{
	float	width;
	float	height;

	width = w_h.x;
	height = w_h.y;
	igSetCursorPos((ImVec2){WINDOW_WIDTH * 0.5f - width * 0.5f, y_pos});
	if (igButton(text, (ImVec2){width, height}))
	{
		if (ft_strcmp(text, "Start Game") == 0)
		{
			game->features.unlock_cursor = false;
			mlx_mouse_hide(game->mlx.ctx);
			game->main_menu = IN_GAME;
		}
		else if (ft_strcmp(text, "Settings") == 0)
			game->main_menu = SETTINGS_MENU;
		else if (ft_strcmp(text, "Back") == 0)
			game->main_menu--;
		else if (ft_strcmp(text, "Controls") == 0)
			game->main_menu = CONTROLS_MENU;
		else if (ft_strcmp(text, "Exit") == 0)
			mlx_loop_end(game->mlx.ctx);
	}
}

static void	draw_title(void)
{
	ImGuiWindowFlags	flags;
	ImVec2				title_size;

	flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
		| ImGuiWindowFlags_NoCollapse;
	igSetNextWindowPos((ImVec2){0, 0}, ImGuiCond_Always, (ImVec2){0, 0});
	igSetNextWindowSize((ImVec2){WINDOW_WIDTH, WINDOW_HEIGHT},
		ImGuiCond_Always);
	igBegin("##Cub3D", NULL, flags);
	igCalcTextSize(&title_size, "Cub3D", NULL, false, 0.0f);
	igSetCursorPos((ImVec2){WINDOW_WIDTH * 0.5f - title_size.x * 0.5f,
		WINDOW_HEIGHT * 0.30f});
	igText("Cub3D");
}

static void	draw_sliders(t_game *game)
{
	float			start_y;
	float			padding;
	static int		fps = DEFAULT_FPS_GOAL;
	static float	sensitivity = DEFAULT_SENSITIVITY;

	start_y = WINDOW_HEIGHT * 0.35f;
	padding = 35.0f;
	igPushItemWidth(300.0f);
	igSetCursorPos((ImVec2){(WINDOW_WIDTH - 300.0f) * 0.5f, start_y + padding});
	if (igSliderInt("##FPS", &fps, 1, 500, "FPS: %d", 0))
		mlx_set_fps_goal(game->mlx.ctx, fps);
	igSetCursorPos((ImVec2){(WINDOW_WIDTH - 300.0f) * 0.5f,
		start_y + padding * 2});
	if (igSliderFloat("##Mouse Sensitivity", &sensitivity,
			0.1f, 10.0f, "Sensitivity: %.1f", 0))
		game->player.sensitivity = sensitivity;
	igPopItemWidth();
}

static void	settings_menu(t_game *game)
{
	draw_sliders(game);
	draw_button("Controls", WINDOW_HEIGHT * 0.53f,
		(t_fvec2d){200.0f, 40.0f}, game);
	draw_button("Back", WINDOW_HEIGHT * 0.60f,
		(t_fvec2d){200.0f, 40.0f}, game);
}

void	draw_window(t_game *game, t_mlx *mlx)
{
	(void) mlx;
	if (game->main_menu == IN_GAME)
		return ;
	draw_title();
	if (game->main_menu == MAIN_MENU || game->main_menu == START_MENU)
	{
		draw_button("Start Game", WINDOW_HEIGHT * 0.5f - 60.0f,
			(t_fvec2d){200.0f, 40.0f}, game);
		draw_button("Settings", WINDOW_HEIGHT * 0.5f,
			(t_fvec2d){200.0f, 40.0f}, game);
		draw_button("Exit", WINDOW_HEIGHT * 0.5f + 60.0f,
			(t_fvec2d){200.0f, 40.0f}, game);
	}
	else if (game->main_menu == SETTINGS_MENU)
		settings_menu(game);
	else if (game->main_menu == CONTROLS_MENU)
	{
		draw_button("Back", WINDOW_HEIGHT * 0.5f,
			(t_fvec2d){200.0f, 40.0f}, game);
	}
	igEnd();
}

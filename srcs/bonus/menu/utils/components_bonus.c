/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:06:58 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:27:03 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_button(const char *text,
	float y_pos, t_fvec2d w_h, t_game *game)
{
	float	width;
	float	height;

	width = w_h.x;
	height = w_h.y;
	igSetCursorPos((ImVec2){WINDOW_WIDTH * 0.5f - width * 0.5f, y_pos});
	if (igButton(text, (ImVec2){width, height}))
	{
		if (ft_strcmp(text, "Play Game") == 0)
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

void	draw_title(void)
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

void	draw_sliders(t_game *game)
{
	float			start_y;
	float			padding;
	static int		fps = DEFAULT_FPS_GOAL;
	static float	sensitivity = DEFAULT_SENSITIVITY;
	static int		plane = DEFAULT_PLANE * 100;

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
	igSetCursorPos((ImVec2){(WINDOW_WIDTH - 300.0f) * 0.5f,
		start_y + padding * 3});
	if (igSliderInt("##Plane", &plane, 10, 110, "Plane X/Y: %d", 0))
	{
		game->player.plane.x = (plane / 100.0f) * game->player.dir.y;
		game->player.plane.y = (plane / 100.0f) * -game->player.dir.x;
	}
	igPopItemWidth();
}

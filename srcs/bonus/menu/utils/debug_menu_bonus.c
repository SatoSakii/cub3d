/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_menu_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:39:55 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:27:05 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	float_to_rgb(t_colors *color, float *color_arr)
{
	color->r = (int)(color_arr[0] * 255.0f);
	color->g = (int)(color_arr[1] * 255.0f);
	color->b = (int)(color_arr[2] * 255.0f);
	color->color = (color->r << 24) | (color->g << 16) | (color->b << 8) | 0xFF;
}

static void	rgb_to_float(t_colors *color, float *color_arr)
{
	color_arr[0] = (float)color->r / 255.0f;
	color_arr[1] = (float)color->g / 255.0f;
	color_arr[2] = (float)color->b / 255.0f;
}

static void	draw_debug_window(t_game *game)
{
	ImGuiWindowFlags	flags;

	flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoSavedSettings;
	igSetNextWindowPos((ImVec2){WINDOW_WIDTH - 20, 20}, ImGuiCond_FirstUseEver,
		(ImVec2){1.0f, 0.0f});
	igSetNextWindowSize((ImVec2){300.0f, 250.0f}, ImGuiCond_FirstUseEver);
	igBegin("Debug Menu", NULL, flags);
	igSeparator();
	igText("\nX:        %6.2f | Y:          %6.2f", game->player.pos.x,
		game->player.pos.y);
	igText("DirX:     %6.2f | DirY:       %6.2f", game->player.dir.x,
		game->player.dir.y);
	igText("PlaneX:   %6.2f | PlaneY:     %6.2f", game->player.plane.x,
		game->player.plane.y);
	igText("Velocity: %6.2f | Sensitivty: %6.2f\n\n", game->player.velocity,
		game->player.sensitivity);
	igSeparator();
}

void	draw_debug_menu(t_game *game)
{
	static float	ceil_arr[3] = {-1.0f, 0.0f, 0.0f};
	static float	floor_arr[3] = {-1.0f, 0.0f, 0.0f};

	draw_debug_window(game);
	if (ceil_arr[0] == -1.0f)
		rgb_to_float(&game->ceiling, ceil_arr);
	if (floor_arr[0] == -1.0f)
		rgb_to_float(&game->floor, floor_arr);
	igText("Ceiling Color");
	if (igColorEdit3("##ceiling", ceil_arr,
			ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB))
		float_to_rgb(&game->ceiling, ceil_arr);
	igText("Floor Color");
	if (igColorEdit3("##floor", floor_arr,
			ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB))
		float_to_rgb(&game->floor, floor_arr);
	igEnd();
}

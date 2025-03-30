/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:08:14 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:27:06 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	settings_menu(t_game *game)
{
	draw_sliders(game);
	draw_button("Controls", WINDOW_HEIGHT * 0.55f,
		(t_fvec2d){200.0f, 40.0f}, game);
	draw_button("Back", WINDOW_HEIGHT * 0.62f,
		(t_fvec2d){200.0f, 40.0f}, game);
}

void	start_menu(t_game *game)
{
	draw_button("Play Game", WINDOW_HEIGHT * 0.5f - 60.0f,
		(t_fvec2d){200.0f, 40.0f}, game);
	draw_button("Settings", WINDOW_HEIGHT * 0.5f,
		(t_fvec2d){200.0f, 40.0f}, game);
	draw_button("Exit", WINDOW_HEIGHT * 0.5f + 60.0f,
		(t_fvec2d){200.0f, 40.0f}, game);
}

void	controls_menu(t_game *game)
{
	int			len;
	int			i;
	t_ivec2d	pos;

	i = -1;
	pos = (t_ivec2d){0, 0};
	len = sizeof(game->controls.keys) / sizeof(game->controls.keys[0]);
	while (++i < len)
	{
		if (game->controls.keys[i].state == WAITING_FOR_INPUT)
			draw_controls_buttons("...", (t_ivec2d){pos.x, pos.y}, game, i);
		else
			draw_controls_buttons(SDL_GetKeyName(
					SDL_GetKeyFromScancode(game->controls.keys[i].keycode)),
				(t_ivec2d){pos.x, pos.y}, game, i);
		if (i % 2 == 1)
		{
			pos.x = 0;
			pos.y++;
		}
		else
			pos.x++;
	}
	draw_button("Back", WINDOW_HEIGHT * 0.74f,
		(t_fvec2d){200.0f, 40.0f}, game);
}

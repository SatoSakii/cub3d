/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:44:40 by albernar          #+#    #+#             */
/*   Updated: 2025/03/23 21:29:09 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event_keyup(int keycode, void *param)
{
	int			len;
	int			i;
	t_game		*game;

	game = (t_game *)param;
	len = sizeof(game->controls.keys) / sizeof(game->controls.keys[0]);
	i = -1;
	if (game->main_menu == IN_GAME && keycode == SDL_SCANCODE_LSHIFT)
		game->player.is_running = false;
	while (++i < len)
	{
		if (keycode == game->controls.keys[i].keycode)
			game->controls.keys[i].state = RELEASE;
	}
}

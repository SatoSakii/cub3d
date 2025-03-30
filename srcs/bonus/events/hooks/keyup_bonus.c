/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:44:40 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:26:47 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	event_keyup(int keycode, void *param)
{
	int			len;
	int			i;
	t_game		*game;

	game = (t_game *)param;
	len = sizeof(game->controls.keys) / sizeof(game->controls.keys[0]);
	i = -1;
	while (++i < len)
	{
		if (keycode == game->controls.keys[i].keycode)
			game->controls.keys[i].state = RELEASE;
	}
	if (game->main_menu == IN_GAME && game->controls.keys[4].state == RELEASE)
		game->player.is_running = false;
}

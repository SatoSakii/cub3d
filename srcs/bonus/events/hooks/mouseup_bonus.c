/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:03:12 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:26:49 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	event_mouseup(int button, void *param)
{
	t_game		*game;

	game = (t_game *)param;
	if (button == SDL_BUTTON_LEFT)
		game->controls.clicks[0].state = RELEASE;
}

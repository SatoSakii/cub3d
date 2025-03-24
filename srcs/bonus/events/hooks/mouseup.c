/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:03:12 by albernar          #+#    #+#             */
/*   Updated: 2025/03/21 17:03:17 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event_mouseup(int button, void *param)
{
	t_game		*game;

	game = (t_game *)param;
	if (button == SDL_BUTTON_LEFT)
		game->controls.clicks[0].state = RELEASE;
}

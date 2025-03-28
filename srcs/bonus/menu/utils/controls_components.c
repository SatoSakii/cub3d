/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_components.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:21:43 by albernar          #+#    #+#             */
/*   Updated: 2025/03/28 23:43:05 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_controls_buttons(const char *text, t_ivec2d pos,
	t_game *game, int i)
{
	t_fvec2d	size;
	t_fvec2d	start;
	float		spacing;

	size.x = 150.0f;
	size.y = 40.0f;
	spacing = 20.0f;
	start.x = WINDOW_WIDTH * 0.5f - size.x - spacing * 0.5f;
	start.y = WINDOW_HEIGHT * 0.4f;
	pos.x = start.x + (pos.x * (size.x + spacing));
	pos.y = start.y + (pos.y * (size.y + spacing));
	igSetCursorPos((ImVec2){pos.x, pos.y});
	if (igButton(text, (ImVec2){size.x, size.y}))
		game->controls.keys[i].state = WAITING_FOR_INPUT;
}

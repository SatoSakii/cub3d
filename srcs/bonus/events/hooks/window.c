/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:42:24 by albernar          #+#    #+#             */
/*   Updated: 2025/03/21 16:47:38 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event_window(int event, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (event == 0)
		mlx_loop_end(game->mlx.ctx);
}

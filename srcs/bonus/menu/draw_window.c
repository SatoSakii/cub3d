/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 02:36:04 by albernar          #+#    #+#             */
/*   Updated: 2025/03/28 22:10:22 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_window(t_game *game, __attribute__ ((unused)) t_mlx *mlx)
{
	if (game->main_menu == IN_GAME)
		return ;
	draw_title();
	if (game->main_menu == MAIN_MENU || game->main_menu == START_MENU)
		start_menu(game);
	else if (game->main_menu == SETTINGS_MENU)
		settings_menu(game);
	else if (game->main_menu == CONTROLS_MENU)
		controls_menu(game);
	igEnd();
}

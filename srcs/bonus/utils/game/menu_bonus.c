/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:46:01 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:27:24 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_tribool	block_game(t_game *game)
{
	if (game->features.unlock_cursor)
		return (TRIBOOL_UNSET);
	if (game->main_menu != IN_GAME)
		return (TRIBOOL_TRUE);
	return (TRIBOOL_FALSE);
}

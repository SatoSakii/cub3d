/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:46:01 by albernar          #+#    #+#             */
/*   Updated: 2025/03/25 03:26:42 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tribool	block_game(t_game *game)
{
	if (game->features.unlock_cursor)
		return (TRIBOOL_UNSET);
	if (game->main_menu != IN_GAME)
		return (TRIBOOL_TRUE);
	return (TRIBOOL_FALSE);
}

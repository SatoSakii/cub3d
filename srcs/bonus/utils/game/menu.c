/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:46:01 by albernar          #+#    #+#             */
/*   Updated: 2025/03/21 19:46:04 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	block_game(t_game *game)
{
	if (game->main_menu != IN_GAME || game->features.unlock_cursor)
		return (true);
	return (false);
}

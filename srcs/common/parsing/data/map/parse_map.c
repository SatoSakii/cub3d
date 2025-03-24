/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:14:25 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 18:11:44 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

int	parse_map(int fd, t_error_ctx *ctx, t_game *game)
{
	fill_map(fd, ctx, game);
	if (!game->map.grid)
		return (PROCESS_ERR);
	if (check_map_validity(game, ctx) == PROCESS_ERR)
		return (PROCESS_ERR);
	return (PROCESS_OK);
}

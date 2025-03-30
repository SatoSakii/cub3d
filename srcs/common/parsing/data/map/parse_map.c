/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:14:25 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:07:33 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

int	check_map_emptyline(t_game *game, t_error_ctx *ctx)
{
	int	i;

	i = 0;
	while (game->map.grid[i])
	{
		if (game->map.grid[i] && game->map.grid[i][0] == '\n'
			&& !game->map.grid[i][1])
		{
			ctx->line_num = (ctx->line_num - game->map.height) + i + 2;
			ctx->line_content = ft_strdup(game->map.grid[i]);
			apply_ctx(ctx, 1, i);
			throw_err(ERR_INVALID_LINE, ctx);
			return (PROCESS_ERR);
		}
		i++;
	}
	return (PROCESS_OK);
}

int	parse_map(int fd, t_error_ctx *ctx, t_game *game)
{
	fill_map(fd, ctx, game);
	if (!game->map.grid)
		return (PROCESS_ERR);
	if (check_map_validity(game, ctx) == PROCESS_ERR)
		return (PROCESS_ERR);
	if (check_map_emptyline(game, ctx) == PROCESS_ERR)
		return (PROCESS_ERR);
	if (map_floodfill(game, ctx) == PROCESS_ERR)
		return (PROCESS_ERR);
	game->map.grid[(int)game->player.pos.y][(int)game->player.pos.x] = '0';
	return (PROCESS_OK);
}

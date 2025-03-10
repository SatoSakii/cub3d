/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 06:56:46 by albernar          #+#    #+#             */
/*   Updated: 2025/03/06 06:56:51 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_pos(t_game *game, int x, int y, char tile)
{
	game->player.pos.x = x + 0.5;
	game->player.pos.y = y + 0.5;
	game->player.dir.x = 0;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0;
	game->player.dir.x = (tile == 'N') * -1 + (tile == 'S') * 1;
	game->player.dir.y = (tile == 'W') * -1 + (tile == 'E') * 1;
	game->player.plane.x = (tile == 'E') * 0.66 + (tile == 'W') * -0.66;
	game->player.plane.y = (tile == 'N') * 0.66 + (tile == 'S') * -0.66;
}

static bool	init_player(t_game *game,
		t_error_ctx *ctx, int xy[2], int *dir_count)
{
	char	tile;
	int		x;
	int		y;

	x = xy[1];
	y = xy[0];
	tile = game->map.grid[y][x];
	(*dir_count)++;
	if (*dir_count > 1)
	{
		ctx->line_num = (ctx->line_num - game->map.height) + y + 2;
		ctx->line_content = game->map.grid[y];
		apply_ctx(ctx, 1, x);
		throw_err(ERR_TOO_MUCH_PLY, ctx);
		return (false);
	}
	set_player_pos(game, x, y, tile);
	return (true);
}

static bool	check_valid_tile(char tile,
		t_error_ctx *ctx, t_game *game, int xy[2])
{
	int	x;
	int	y;

	x = xy[1];
	y = xy[0];
	if (!ft_isspace(tile)
		&& !ft_strchr(get_event_charset(1, get_events_tile()), tile))
	{
		ctx->line_num = (ctx->line_num - game->map.height) + y + 2;
		ctx->line_content = game->map.grid[y];
		apply_ctx(ctx, 1, x);
		throw_err(ERR_INVALID_TILE, ctx);
		return (false);
	}
	return (true);
}

static int	check_no_player(int dir_count, t_error_ctx *ctx)
{
	if (dir_count == 0)
	{
		ctx->line_content = get_event_charset(1, get_events_directions());
		apply_ctx(ctx, ft_strlen(ctx->line_content), 0);
		throw_err(ERR_NO_PLY, ctx);
		return (PROCESS_ERR);
	}
	return (PROCESS_OK);
}

int	check_map_validity(t_game *game, t_error_ctx *ctx)
{
	int		x;
	int		y;
	int		dir_count;
	char	tile;

	dir_count = 0;
	y = -1;
	while (game->map.grid[++y])
	{
		x = -1;
		while (game->map.grid[y][++x])
		{
			tile = game->map.grid[y][x];
			if (ft_strchr(get_event_charset(1, get_events_directions()), tile))
			{
				if (!init_player(game, ctx, (int [2]){y, x}, &dir_count))
					return (PROCESS_ERR);
			}
			else
				if (!check_valid_tile(tile, ctx, game, (int [2]){y, x}))
					return (PROCESS_ERR);
		}
	}
	return (check_no_player(dir_count, ctx));
}

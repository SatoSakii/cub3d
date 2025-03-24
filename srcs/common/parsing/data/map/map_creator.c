/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 05:58:42 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 18:11:44 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

static bool	resize_map(t_game *game, t_error_ctx *ctx, int *size)
{
	char	**new_grid;

	*size <<= 2;
	new_grid = ft_realloc(game->map.grid,
			sizeof(char *) * game->map.height, sizeof(char *) * (*size));
	if (!new_grid)
	{
		apply_ctx(ctx, -1, -1);
		ctx->line_content = NULL;
		throw_err(ERR_MALLOC, ctx);
		return (false);
	}
	game->map.grid = new_grid;
	return (true);
}

static bool	process_map(t_game *game, t_error_ctx *ctx,
	int *size, bool *valid_line)
{
	char	*line;

	ctx->line_num++;
	line = ctx->line_content;
	skip_spaces(&line);
	if (!*line && !*valid_line)
		return (false);
	*valid_line = true;
	if (game->map.height >= *size)
		if (!resize_map(game, ctx, size))
			return (false);
	game->map.grid[game->map.height] = ctx->line_content;
	if (game->map.width < (int)ft_strlen(ctx->line_content))
		game->map.width = ft_strlen(ctx->line_content);
	return (true);
}

static bool	init_grid(int size, t_error_ctx *ctx, t_game *game)
{
	game->map.grid = malloc(sizeof(char *) * (size + 1));
	if (!game->map.grid)
	{
		apply_ctx(ctx, -1, -1);
		ctx->line_content = NULL;
		throw_err(ERR_MALLOC, ctx);
		return (false);
	}
	return (true);
}

void	fill_map(int fd, t_error_ctx *ctx, t_game *game)
{
	int		size;
	bool	valid_line;
	char	*line;

	size = 8;
	valid_line = false;
	if (!init_grid(size, ctx, game))
		return ;
	if (!game->map.grid)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		ctx->line_content = line;
		if (!process_map(game, ctx, &size, &valid_line))
		{
			free(ctx->line_content);
			line = get_next_line(fd);
			return ;
		}
		game->map.height++;
		line = get_next_line(fd);
	}
	game->map.grid[game->map.height] = NULL;
}

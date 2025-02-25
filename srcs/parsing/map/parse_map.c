/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:35:18 by albernar          #+#    #+#             */
/*   Updated: 2025/02/25 19:31:58 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// free 2dptr if realloc failed
void	fill_map(int fd, t_error_ctx *ctx, t_game *game)
{
	size_t	size;
	size_t	count;
	t_bool	valid_line_encountered;
	char	*line;

	size = 8;
	count = 0;
	valid_line_encountered = FALSE;
	game->map.grid = malloc(sizeof(char *) * size);
	if (!game->map.grid)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		ctx->line_num++;
		ctx->line_content = line;
		skip_spaces(&line);
		if (!*line && !valid_line_encountered)
		{
			free(ctx->line_content);
			line = get_next_line(fd);
			continue ;
		}
		game->map.grid_size++;
		line = ctx->line_content;
		valid_line_encountered = TRUE;
		if (count >= size)
		{
			size <<= 1;
			game->map.grid = ft_realloc(game->map.grid, count * sizeof(char *),
					(size + 1) * sizeof(char *));
			if (!game->map.grid)
				return ;
		}
		game->map.grid[count++] = line;
		line = get_next_line(fd);
	}
	game->map.grid[count] = NULL;
}

t_bool	map_isvalid(char **map, t_error_ctx *ctx, t_game *game)
{
	int		direction_count;
	char	tile;
	int		y;
	int		x;

	y = -1;
	if (!map || !*map)
		return (FALSE);
	direction_count = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			tile = map[y][x];
			if (ft_strchr(MAP_DIRECTIONS, tile))
			{
				direction_count++;
				game->player.pos.x = x + 0.5;
				game->player.pos.y = y + 0.5;
				if (tile == 'N' || tile == 'S')
				{
					game->player.plane.x = 0.70;
					game->player.plane.y = 0;
					game->player.dir.y = -1;
					if (tile == 'S')
					{
						game->player.plane.x = -0.70;
						game->player.dir.y = 1;
					}
					game->player.dir.x = 0;
				}
				else if (tile == 'W' || tile == 'E')
				{
					game->player.plane.y = 0.70;
					game->player.plane.x = 0;
					game->player.dir.x = 1;
					if (tile == 'W')
					{
						game->player.plane.y = -0.70;
						game->player.plane.x = 0;
						game->player.dir.x = -1;
					}
					game->player.dir.y = 0;
				}
				if (direction_count > 1)
					break ;
			}
			else if (!ft_isspace(tile) && !ft_strchr(MAP_TILES, tile))
			{
				ctx->line_num = (ctx->line_num - game->map.grid_size) + y + 2;
				ctx->line_content = map[y];
				apply_ctx(ctx, 1, x);
				throw_err(ERR_INVALID_TILE, ctx);
				return (FALSE);
			}
		}
		if (direction_count > 1)
			break ;
	}
	if (direction_count != 1)
	{
		ctx->line_num = (ctx->line_num - game->map.grid_size) + y + 2;
		ctx->line_content = map[y];
		apply_ctx(ctx, 1, x);
		throw_err(ERR_TOO_MUCH_PLY, ctx);
	}
	return (direction_count == 1);
}

int	parse_map(int fd, t_error_ctx *ctx, t_game *game)
{
	fill_map(fd, ctx, game);
	if (!game->map.grid)
		return (PROCESS_ERR);
	if (!map_isvalid(game->map.grid, ctx, game))
		return (PROCESS_ERR);
	return (PROCESS_OK);
}

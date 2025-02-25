/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:27:55 by albernar          #+#    #+#             */
/*   Updated: 2025/02/25 14:36:16 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	info_hasspace(char *line, t_error_ctx *ctx)
{
	if (!ft_isspace(*line))
	{
		apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
		throw_err(ERR_INVALID_LINE, ctx);
		return (PROCESS_ERR);
	}
	return (PROCESS_OK);
}

void	skip_spaces(char **line)
{
	if (!line || !*line)
		return ;
	while (**line && ft_isspace((unsigned char)**line))
		(*line)++;
}

int	check_line_validity(t_error_ctx *ctx, char *line, int *found)
{
	const char	*valid_keywords[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int			i;

	ctx->line_content = line;
	skip_spaces(&line);
	if (*line == '\n' || *line == '\0')
		return (PROCESS_SKIP_LINE);
	i = -1;
	while (valid_keywords[++i])
	{
		if (!ft_strncmp(line, valid_keywords[i], ft_strlen(valid_keywords[i])))
		{
			(*found)++;
			return (PROCESS_OK);
		}
	}
	if (*line == '1' || *line == '0' || *line == 'E'
		|| *line == 'N' || *line == 'W' || *line == 'S')
		return (PROCESS_SKIP_LINE);
	apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
	throw_err(ERR_INVALID_LINE, ctx);
	return (PROCESS_ERR);
}

void	free_game(t_game *game)
{
	if (game->ea.addr)
		free(game->ea.addr);
	if (game->no.addr)
		free(game->no.addr);
	if (game->so.addr)
		free(game->so.addr);
	if (game->we.addr)
		free(game->we.addr);
	if (game->map.grid)
		ft_free2d((void **)game->map.grid);
}

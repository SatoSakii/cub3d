/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 01:18:36 by albernar          #+#    #+#             */
/*   Updated: 2025/03/07 21:13:06 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	info_hasspace(char **line, t_error_ctx *ctx, t_event *event)
{
	event->found = true;
	if (!ft_isspace(**line))
	{
		apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
		throw_err(ERR_INVALID_LINE, ctx);
		return (PROCESS_ERR);
	}
	skip_spaces(line);
	return (PROCESS_OK);
}

void	skip_spaces(char **line)
{
	if (!line || !*line)
		return ;
	while (**line && ft_isspace((unsigned char)**line))
		(*line)++;
}

int	check_charset(char *line, char *charset, int step)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(charset))
	{
		if (!ft_strncmp(line, charset + i, step))
			return (1);
		i += step;
	}
	return (0);
}

int	check_line_validity(t_error_ctx *ctx, char *line, int *found)
{
	char		*charset;

	ctx->line_content = line;
	skip_spaces(&line);
	if (!*line || *line == '\n')
		return (PROCESS_SKIP_LINE);
	charset = get_event_charset(1, get_events_texture());
	if (check_charset(line, charset, TEX_LEN))
	{
		(*found)++;
		return (PROCESS_OK);
	}
	charset = get_event_charset(1, get_events_color());
	if (check_charset(line, charset, COLOR_LEN))
	{
		(*found)++;
		return (PROCESS_OK);
	}
	charset = get_event_charset(2, get_events_tile(), get_events_directions());
	if ((!ft_isspace(line[TEX_LEN]) && !ft_isspace(line[COLOR_LEN]))
		|| !check_charset(line, charset, TILE_LEN))
		return (PROCESS_SKIP_LINE);
	apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
	throw_err(ERR_INVALID_LINE, ctx);
	return (PROCESS_ERR);
}

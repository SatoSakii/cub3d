/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 01:12:43 by albernar          #+#    #+#             */
/*   Updated: 2025/03/07 22:41:50 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_missing(char *line, int found, int max_found, t_error_ctx *ctx)
{
	char		final_str[((MAX_TEXTURES * TEX_LEN + MAX_COLORS * COLOR_LEN)
			<< 1) + 1];
	t_event		*event;
	int			i;

	ft_memset(final_str, 0, sizeof(final_str));
	if (!line && found < max_found)
	{
		event = get_events();
		i = -1;
		while (event[++i].name)
		{
			if (!event[i].found
				&& (event[i].type != TILE || event[i].type != DIRECTIONS))
				ft_strcat(ft_strcat(final_str, event[i].name), ", ");
		}
		final_str[ft_strlen(final_str) - 2] = 0;
		ctx->line_content = final_str;
		apply_ctx(ctx, ft_strlen(event[i].name), 0);
		throw_err(ERR_MISSING_INFO, ctx);
		return (PROCESS_ERR);
	}
	return (PROCESS_OK);
}

static int	finalize_parsing(char *l, int found,
	int max_found, t_error_ctx *ctx)
{
	ctx->line_content = l;
	if (check_missing(l, found, max_found, ctx) == PROCESS_ERR)
		return (PROCESS_ERR);
	skip_spaces(&l);
	apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
	if (l && *l
		&& (ft_strnstr(get_event_charset(1, get_events_color()), l, COLOR_LEN)
			|| ft_strnstr(get_event_charset(1,
					get_events_texture()), l, TEX_LEN)))
	{
		if (ft_strchr(get_event_charset(1, get_events_color()), *l))
			throw_err(ERR_DUPLICATE_COLOR, ctx);
		else
			throw_err(ERR_DUPLICATE_TEXTURE, ctx);
		return (PROCESS_ERR);
	}
	if (*l)
	{
		throw_err(ERR_INVALID_LINE, ctx);
		return (PROCESS_ERR);
	}
	free(ctx->line_content);
	return (PROCESS_OK);
}

static int	process_line(char *line, t_error_ctx *ctx, int *found)
{
	int	err;

	err = check_line_validity(ctx, line, found);
	if (err == PROCESS_ERR)
		return (PROCESS_ERR);
	else if (err == PROCESS_SKIP_LINE)
		return (PROCESS_SKIP_LINE);
	err = handle_texture(line, ctx);
	if (err == PROCESS_ERR)
		return (PROCESS_ERR);
	else if (err == PROCESS_SKIP_LINE)
		return (PROCESS_SKIP_LINE);
	err = handle_color(line, ctx);
	if (err == PROCESS_ERR)
		return (PROCESS_ERR);
	return (PROCESS_OK);
}

int	parse_data(int fd, t_error_ctx *ctx)
{
	int			err;
	int			found;
	const int	max_found = get_event_len(get_events_texture())
		+ get_event_len(get_events_color());
	static int	line_num = 0;
	char		*line;

	found = 0;
	line = get_next_line(fd);
	while (found < max_found && line && ++line_num > 0)
	{
		ctx->line_num = line_num;
		err = process_line(line, ctx, &found);
		if (err == PROCESS_ERR)
			return (PROCESS_ERR);
		else if (err == PROCESS_SKIP_LINE)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		line = get_next_line(fd);
	}
	return (finalize_parsing(line, found, max_found, ctx));
}

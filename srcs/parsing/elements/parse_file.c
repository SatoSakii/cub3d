/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:28:50 by albernar          #+#    #+#             */
/*   Updated: 2025/02/23 17:50:23 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_line(char *line, t_error_ctx *ctx, t_game *game, int *found)
{
	int	err;

	err = check_line_validity(ctx, line, found);
	if (err == PROCESS_ERR)
		return (PROCESS_ERR);
	else if (err == PROCESS_SKIP_LINE)
		return (PROCESS_SKIP_LINE);
	err = handle_texture(line, ctx, game);
	if (err == PROCESS_ERR)
		return (PROCESS_ERR);
	else if (err == PROCESS_SKIP_LINE)
		return (PROCESS_SKIP_LINE);
	err = handle_color(line, ctx, game);
	if (err == PROCESS_ERR)
		return (PROCESS_ERR);
	return (PROCESS_OK);
}

static int	finalize_parsing(char *l, int found, t_error_ctx *ctx)
{
	ctx->line_content = l;
	if (!l && found < 6)
	{
		apply_ctx(ctx, ft_strlen(ctx->args[0]) + 1, ft_strlen(ctx->filename));
		throw_err(ERR_MISSING_INFO, ctx);
		return (PROCESS_ERR);
	}
	skip_spaces(&l);
	apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
	if (l && (!ft_strncmp(l, "SO", 2) || !ft_strncmp(l, "NO", 2) || *l == 'C'
			|| !ft_strncmp(l, "EA", 2) || !ft_strncmp(l, "WE", 2) || *l == 'F'))
	{
		if (*l == 'C' || *l == 'F')
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

int	parse_data(int fd, t_error_ctx *ctx, t_game *game)
{
	int			err;
	int			found;
	static int	line_num = 0;
	char		*line;

	found = 0;
	line = get_next_line(fd);
	while (found < 6 && line && ++line_num > 0)
	{
		ctx->line_num = line_num;
		err = process_line(line, ctx, game, &found);
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
	return (finalize_parsing(line, found, ctx));
}

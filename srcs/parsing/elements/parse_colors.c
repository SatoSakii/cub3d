/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:07:18 by albernar          #+#    #+#             */
/*   Updated: 2025/02/23 17:04:56 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_rgb(char **line)
{
	int	value;

	skip_spaces(line);
	value = 0;
	if (line && *line && **line && **line == '+')
		(*line)++;
	if (!**line || !ft_isdigit((unsigned char)**line))
		return (-1);
	while (**line && ft_isdigit((unsigned char)**line))
	{
		value = value * 10 + (**line - '0');
		(*line)++;
	}
	if (value < 0 || value > 255)
		return (-1);
	skip_spaces(line);
	return (value);
}

static int	check_next_color(t_error_ctx *ctx, int i, char **line, int *comma)
{
	if (i < 2 && line && *line && **line == ',')
	{
		(*comma)++;
		(*line)++;
		skip_spaces(line);
	}
	else if (i < 2)
	{
		throw_err(ERR_INVALID_COLOR, ctx);
		return (PROCESS_ERR);
	}
	return (PROCESS_OK);
}

static int	parse_color(t_error_ctx *ctx, char *line, t_colors *color)
{
	int			i;
	int			comma;
	const int	*c[] = {&color->r, &color->g, &color->b};

	comma = 0;
	i = -1;
	while (++i < 3)
	{
		*(int *)(uintptr_t)c[i] = parse_rgb(&line);
		if (*(int *)(uintptr_t)c[i] == -1)
		{
			throw_err(ERR_INVALID_COLOR, ctx);
			return (PROCESS_ERR);
		}
		skip_spaces(&line);
		if (check_next_color(ctx, i, &line, &comma) == -1)
			return (PROCESS_ERR);
	}
	if (comma != 2 || *line)
	{
		throw_err(ERR_INVALID_COLOR, ctx);
		return (PROCESS_ERR);
	}
	free(ctx->line_content);
	return (PROCESS_OK);
}

int	handle_color(char *line, t_error_ctx *ctx, t_game *game)
{
	const char		*ids[2] = {"F", "C"};
	const t_colors	*colors[] = {&game->floor, &game->ceiling};
	int				i;

	ctx->line_content = line;
	skip_spaces(&line);
	i = -1;
	while (++i < 2)
	{
		if (!ft_strncmp(line, ids[i], 1))
		{
			line++;
			if (info_hasspace(line, ctx) == PROCESS_ERR)
				return (PROCESS_ERR);
			skip_spaces(&line);
			apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
			if (colors[i]->r != -1)
			{
				throw_err(ERR_DUPLICATE_COLOR, ctx);
				return (PROCESS_ERR);
			}
			return (parse_color(ctx, line, (t_colors *)colors[i]));
		}
	}
	return (PROCESS_OK);
}

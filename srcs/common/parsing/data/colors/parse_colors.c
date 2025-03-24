/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:47:50 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 18:11:44 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

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

static unsigned int	create_rgba(t_colors *color)
{
	return (color->r << 24 | color->g << 16 | color->b << 8 | 0xFF);
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
		throw_err(ERR_INVALID_COLOR, ctx);
	if (comma != 2 || *line)
		return (PROCESS_ERR);
	color->color = create_rgba(color);
	free(ctx->line_content);
	return (PROCESS_OK);
}

int	handle_color(char *l, t_error_ctx *ctx)
{
	const t_event	*e = get_events();
	const int		e_len = get_event_len((t_event *)e);
	int				i;

	ctx->line_content = l;
	skip_spaces(&l);
	i = -1;
	while (++i < e_len)
	{
		if (!ft_strncmp(l, e[i].name, COLOR_LEN) && ft_isspace(l[COLOR_LEN])
			&& e[i].type == COLOR)
		{
			l += COLOR_LEN;
			if (info_hasspace(&l, ctx, (t_event *)&e[i]) == PROCESS_ERR)
				return (PROCESS_ERR);
			apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
			if (((t_colors *)(e[i].data))->r != -1)
			{
				throw_err(ERR_DUPLICATE_COLOR, ctx);
				return (PROCESS_ERR);
			}
			return (parse_color(ctx, l, ((t_colors *)(e[i].data))));
		}
	}
	return (PROCESS_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:05:08 by albernar          #+#    #+#             */
/*   Updated: 2025/03/10 19:22:34 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_parser.h"

int	get_event_len(t_event *event)
{
	int	i;

	i = 0;
	while (event[i].name)
		i++;
	return (i);
}

char	*get_event_charset(int n_args, ...)
{
	int			ijk[3];
	t_event		*event;
	va_list		args;
	static char	charset[MAX_TEXTURES * TEX_LEN
		+ MAX_TILES * TILE_LEN + MAX_COLORS * COLOR_LEN
		+ MAX_DIRECTIONS * DIR_LEN + 1] = {0};

	ft_memset(ijk, 0, sizeof(ijk));
	ft_memset(charset, 0, sizeof(charset));
	va_start(args, n_args);
	while (ijk[2] < n_args)
	{
		event = va_arg(args, t_event *);
		ijk[0] = 0;
		while (event[ijk[0]].name)
		{
			ft_strncpy(&charset[ijk[1]],
				event[ijk[0]].name, sizeof(charset) - ijk[1] - 1);
			ijk[1] += ft_strlen(event[ijk[0]].name);
			ijk[0]++;
		}
		ijk[2]++;
	}
	va_end(args);
	return (charset);
}

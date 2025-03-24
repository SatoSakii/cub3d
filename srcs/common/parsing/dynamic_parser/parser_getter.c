/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:26:40 by albernar          #+#    #+#             */
/*   Updated: 2025/03/06 06:57:32 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_parser.h"

t_event	*get_events(void)
{
	return (event_manager(NULL, 0, NULL, GET));
}

t_event	*get_event(char *name)
{
	int			i;
	t_event		*event;

	i = 0;
	event = get_events();
	while (event[i].name)
	{
		if (!ft_strcmp(event[i].name, name))
			return (&event[i]);
		i++;
	}
	return (NULL);
}

t_event	*get_event_tile(char *name)
{
	int			i;
	t_event		*event;

	i = 0;
	event = get_events();
	while (event[i].name)
	{
		if (event[i].type == TILE && !ft_strncmp(event[i].name,
				name, TILE_LEN))
			return (&event[i]);
		i++;
	}
	return (NULL);
}

t_event	*get_event_color(char *name)
{
	int			i;
	t_event		*event;

	i = 0;
	event = get_events();
	while (event[i].name)
	{
		if (event[i].type == COLOR && !ft_strncmp(event[i].name,
				name, COLOR_LEN))
			return (&event[i]);
		i++;
	}
	return (NULL);
}

t_event	*get_event_texture(char *name)
{
	int			i;
	t_event		*event;

	i = 0;
	event = get_events();
	while (event[i].name)
	{
		if (event[i].type == TEXTURE && !ft_strncmp(event[i].name,
				name, TEX_LEN))
			return (&event[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getter_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:30:58 by albernar          #+#    #+#             */
/*   Updated: 2025/03/06 06:57:32 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_parser.h"

t_event	*get_events_texture(void)
{
	int				i;
	int				j;
	t_event			*event;
	static t_event	events_texture[MAX_TEXTURES + 1] = {0};

	i = 0;
	j = 0;
	event = get_events();
	while (event[i].name)
	{
		if (event[i].type == TEXTURE)
			events_texture[j++] = event[i];
		i++;
	}
	return (events_texture);
}

t_event	*get_events_tile(void)
{
	int				i;
	int				j;
	t_event			*event;
	static t_event	events_tile[MAX_TILES + 1] = {0};

	i = 0;
	j = 0;
	event = get_events();
	while (event[i].name)
	{
		if (event[i].type == TILE)
			events_tile[j++] = event[i];
		i++;
	}
	return (events_tile);
}

t_event	*get_events_color(void)
{
	int				i;
	int				j;
	t_event			*event;
	static t_event	events_color[MAX_COLORS + 1] = {0};

	i = 0;
	j = 0;
	event = get_events();
	while (event[i].name)
	{
		if (event[i].type == COLOR)
			events_color[j++] = event[i];
		i++;
	}
	return (events_color);
}

t_event	*get_events_directions(void)
{
	int				i;
	int				j;
	t_event			*event;
	static t_event	events_directions[MAX_DIRECTIONS + 1] = {0};

	i = 0;
	j = 0;
	event = get_events();
	while (event[i].name)
	{
		if (event[i].type == DIRECTIONS)
			events_directions[j++] = event[i];
		i++;
	}
	return (events_directions);
}

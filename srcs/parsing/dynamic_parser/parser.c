/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:49 by albernar          #+#    #+#             */
/*   Updated: 2025/03/06 21:07:05 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_parser.h"

void	*event_manager(char *name, t_event_type type,
		void *data, t_emanager_type action)
{
	static int		i = 0;
	static t_event	events[MAX_TILES + MAX_COLORS
		+ MAX_TEXTURES + MAX_DIRECTIONS + 1] = {0};

	if (action == REGISTER)
	{
		if (i >= MAX_TILES + MAX_COLORS + MAX_TEXTURES)
			return (NULL);
		events[i].name = name;
		events[i].type = type;
		events[i].data = data;
		events[i].found = false;
		if (type == TILE || type == DIRECTIONS)
			events[i].found = true;
		i++;
	}
	else if (action == GET)
		return (&events);
	return (NULL);
}

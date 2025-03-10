/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_register.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 06:29:10 by albernar          #+#    #+#             */
/*   Updated: 2025/03/06 06:57:32 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_parser.h"

void	register_event(char *name, t_event_type type, void *data)
{
	event_manager(name, type, data, REGISTER);
}

void	register_texture(char *name, t_textures *texture)
{
	register_event(name, TEXTURE, texture);
}

void	register_color(char *name, t_colors *color)
{
	register_event(name, COLOR, color);
}

void	register_tile(char *name)
{
	register_event(name, TILE, NULL);
}

void	register_direction(char *name)
{
	register_event(name, DIRECTIONS, NULL);
}

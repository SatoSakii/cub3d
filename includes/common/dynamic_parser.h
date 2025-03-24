/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 06:57:48 by albernar          #+#    #+#             */
/*   Updated: 2025/03/19 21:23:20 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_PARSER_H
# define DYNAMIC_PARSER_H
# define MAX_TEXTURES 10
# define MAX_COLORS 10
# define MAX_TILES 10
# define MAX_DIRECTIONS 4
# define TILE_LEN 1
# define DIR_LEN TILE_LEN
# define COLOR_LEN 1
# define TEX_LEN 2
# include <stdbool.h>
# include "libft.h"

typedef struct s_colors		t_colors;
typedef struct s_textures	t_textures;

typedef enum e_event_type
{
	TILE = 0,
	DIRECTIONS = 1,
	COLOR = 2,
	TEXTURE = 3
}	t_event_type;

typedef enum e_emanager_type
{
	REGISTER = 0,
	GET = 1
}	t_emanager_type;

typedef struct s_event
{
	char			*name;
	t_event_type	type;
	void			*data;
	bool			found;
}	t_event;

// Event Manager
void	*event_manager(char *name, t_event_type type,
			void *data, t_emanager_type action);

// Event Register
void	register_event(char *name, t_event_type type, void *data);
void	register_texture(char *name, t_textures *texture);
void	register_color(char *name, t_colors *color);
void	register_tile(char *name);
void	register_direction(char *name);

// Event Getter
t_event	*get_events(void);
t_event	*get_event(char *name);
t_event	*get_event_tile(char *name);
t_event	*get_event_color(char *name);
t_event	*get_event_texture(char *name);

// Event Getter List
t_event	*get_events_directions(void);
t_event	*get_events_tile(void);
t_event	*get_events_color(void);
t_event	*get_events_texture(void);

// Event Utils
char	*get_event_charset(int n_args, ...);
int		get_event_len(t_event *event);

#endif
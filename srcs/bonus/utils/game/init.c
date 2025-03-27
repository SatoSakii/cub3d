/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:31:37 by albernar          #+#    #+#             */
/*   Updated: 2025/03/27 22:50:59 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(t_game *game)
{
	register_tile("1");
	register_tile("0");
	register_direction("N");
	register_direction("S");
	register_direction("E");
	register_direction("W");
	register_color("F", &game->floor);
	register_color("C", &game->ceiling);
	register_texture("NO", &game->no);
	register_texture("SO", &game->so);
	register_texture("WE", &game->we);
	register_texture("EA", &game->ea);
}

/*
	0: W
	1: S
	2: A
	3: D
	4: LSHIFT
	5: Q
	6: E
	7: F
*/

static void	init_controls(t_controls *controls)
{
	controls->keys[0] = (t_keybinds){SDL_SCANCODE_W, RELEASE};
	controls->keys[1] = (t_keybinds){SDL_SCANCODE_S, RELEASE};
	controls->keys[2] = (t_keybinds){SDL_SCANCODE_A, RELEASE};
	controls->keys[3] = (t_keybinds){SDL_SCANCODE_D, RELEASE};
	controls->keys[4] = (t_keybinds){SDL_SCANCODE_LSHIFT, RELEASE};
	controls->keys[5] = (t_keybinds){SDL_SCANCODE_Q, RELEASE};
	controls->keys[6] = (t_keybinds){SDL_SCANCODE_E, RELEASE};
	controls->keys[7] = (t_keybinds){SDL_SCANCODE_F, RELEASE};
}

void	init_game(t_game *game, t_error_ctx *ctx)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(ctx, 0, sizeof(t_error_ctx));
	ft_memset(&game->ceiling, -1, sizeof(t_colors));
	ft_memset(&game->floor, -1, sizeof(t_colors));
	init_map(game);
	game->main_menu = START_MENU;
	game->features.unlock_cursor = true;
	game->player.sensitivity = 1.0;
	init_controls(&game->controls);
}

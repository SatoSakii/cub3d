/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:41:53 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:28:41 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	handle_escape_menu(t_game *game)
{
	if (game->main_menu == START_MENU)
		mlx_loop_end(game->mlx.ctx);
	else if (game->main_menu == IN_GAME || game->main_menu == MAIN_MENU)
	{
		if (game->main_menu == IN_GAME)
		{
			mlx_mouse_show(game->mlx.ctx);
			game->main_menu = MAIN_MENU;
		}
		else if (game->main_menu == MAIN_MENU)
		{
			mlx_mouse_hide(game->mlx.ctx);
			mlx_mouse_move(game->mlx.ctx, game->mlx.win,
				(WINDOW_WIDTH >> 1), (WINDOW_HEIGHT >> 1));
			game->main_menu = IN_GAME;
		}
	}
}

static void	handle_change_keybinds(t_game *game, int keycode)
{
	const int	len = sizeof(game->controls.keys)
		/ sizeof(game->controls.keys[0]);
	int			i;

	i = -1;
	while (++i < len)
	{
		if (game->controls.keys[i].state == WAITING_FOR_INPUT)
		{
			game->controls.keys[i].keycode = keycode;
			game->controls.keys[i].state = RELEASE;
			break ;
		}
	}
}

static void	handle_unlock_cursor(t_game *game)
{
	if (!game->features.unlock_cursor)
		mlx_mouse_show(game->mlx.ctx);
	else
	{
		mlx_mouse_move(game->mlx.ctx, game->mlx.win,
			(WINDOW_WIDTH >> 1), (WINDOW_HEIGHT >> 1));
		mlx_mouse_hide(game->mlx.ctx);
	}
	game->features.unlock_cursor = !game->features.unlock_cursor;
}

void	event_keydown(int keycode, void *param)
{
	int			len;
	int			i;
	t_game		*game;

	game = (t_game *)param;
	len = sizeof(game->controls.keys) / sizeof(game->controls.keys[0]);
	i = -1;
	if (keycode == SDL_SCANCODE_ESCAPE)
		handle_escape_menu(game);
	if (keycode == SDL_SCANCODE_F3)
		handle_unlock_cursor(game);
	if (keycode == SDL_SCANCODE_INSERT)
		game->features.show_debug_menu = !game->features.show_debug_menu;
	while (++i < len)
		if (keycode == game->controls.keys[i].keycode)
			game->controls.keys[i].state = DOWN;
	if (game->main_menu == IN_GAME && game->controls.keys[4].state == DOWN)
		game->player.is_running = true;
	if (game->main_menu == IN_GAME && game->controls.keys[5].state == DOWN)
		destroy_wall(game);
	if (game->main_menu == IN_GAME && game->controls.keys[6].state == DOWN)
		restore_wall(game);
	if (game->main_menu == IN_GAME && game->controls.keys[7].state == DOWN)
		open_door(game);
	handle_change_keybinds(game, keycode);
}

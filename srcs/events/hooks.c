/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:10:53 by albernar          #+#    #+#             */
/*   Updated: 2025/03/11 16:44:36 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event_keydown(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == SDL_SCANCODE_ESCAPE)
		mlx_loop_end(game->mlx.ctx);
	else if (keycode == SDL_SCANCODE_W)
		game->keys.w = true;
	else if (keycode == SDL_SCANCODE_S)
		game->keys.s = true;
	else if (keycode == SDL_SCANCODE_A)
		game->keys.a = true;
	else if (keycode == SDL_SCANCODE_D)
		game->keys.d = true;
	else if (keycode == SDL_SCANCODE_N)
		game->collision = !game->collision;
}

void	event_keyup(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == SDL_SCANCODE_W)
		game->keys.w = false;
	else if (keycode == SDL_SCANCODE_S)
		game->keys.s = false;
	else if (keycode == SDL_SCANCODE_A)
		game->keys.a = false;
	else if (keycode == SDL_SCANCODE_D)
		game->keys.d = false;
}

void	event_loop(void *param)
{
	t_game	*game;
	double	delta_time;

	delta_time = get_delta_time();
	game = (t_game *)param;
	if (game->keys.w)
		move_player(game, &game->player, MOVE_FORWARD, delta_time);
	if (game->keys.s)
		move_player(game, &game->player, MOVE_BACKWARD, delta_time);
	if (game->keys.a)
		move_player(game, &game->player, MOVE_LEFT, delta_time);
	if (game->keys.d)
		move_player(game, &game->player, MOVE_RIGHT, delta_time);
	rotate_player(game, &game->player, delta_time);
	mlx_clear_window(game->mlx.ctx, game->mlx.win,
		(mlx_color){.rgba = 0x000000FF});
	raycast(game);
	print_fps();
}

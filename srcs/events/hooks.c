/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:10:53 by albernar          #+#    #+#             */
/*   Updated: 2025/03/19 15:46:21 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/socket.h>

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
	else if (keycode == SDL_SCANCODE_Q)
		destroy_wall(game);
	else if (keycode == SDL_SCANCODE_E)
		restore_wall(game);
	else if (keycode == SDL_SCANCODE_LSHIFT)
		game->player.is_running = true;
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
	else if (keycode == SDL_SCANCODE_LSHIFT)
		game->player.is_running = false;
}

void	update_packet(t_packet *packet, t_game *game)
{
	packet->px = game->player.pos.x;
	packet->py = game->player.pos.y;
	packet->wx = 0;
	packet->wy = 0;
	packet->shoot = 0;
}

void	event_loop(void *param)
{
	t_game	*game;
	double	delta_time;
	t_packet	packet;

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
	update_packet(&packet, game);
	ssize_t bytes_send = send(game->client_socket, &packet, sizeof(packet), MSG_CONFIRM);
	if (bytes_send < 0)
		perror("send");
	printf("Nombre de bytes envoyees = %zd\n", bytes_send);
	mlx_pixel_put_array(game->mlx.ctx, game->mlx.win,
		0, 0, game->scene, WINDOW_WIDTH * WINDOW_HEIGHT);
	mlx_put_image_to_window(game->mlx.ctx, game->mlx.win, game->crosshair.img,
		WINDOW_WIDTH / 2 - game->crosshair.width / 2,
		WINDOW_HEIGHT / 2 - game->crosshair.height / 2);
	//print_fps();
}

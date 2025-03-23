/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:10:53 by albernar          #+#    #+#             */
/*   Updated: 2025/03/23 14:02:35 by stetrel          ###   ########.fr       */
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
	packet->speed = SPEED_FACTOR;
	packet->shoot = 0;
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
	update_packet(&game->packet, game);
	ssize_t bytes_send = send(game->client_socket, &game->packet, sizeof(game->packet), MSG_CONFIRM);
	if (bytes_send < 0)
		perror("send");
	int bytes_read = read(game->client_socket, &game->packet, sizeof(game->packet));
	if (bytes_read < 0)
		perror("read");
	if (game->packet.wx < 0)
		game->map.grid[abs(game->packet.wy)][abs(game->packet.wx)] = '1';
	else
		game->map.grid[game->packet.wy][game->packet.wx] = '0';
	memset(&game->packet, 0, sizeof(game->packet));
	mlx_pixel_put_array(game->mlx.ctx, game->mlx.win,
		0, 0, game->scene, WINDOW_WIDTH * WINDOW_HEIGHT);
	mlx_put_image_to_window(game->mlx.ctx, game->mlx.win, game->crosshair.img,
		WINDOW_WIDTH / 2 - game->crosshair.width / 2,
		WINDOW_HEIGHT / 2 - game->crosshair.height / 2);
	//print_fps();
}

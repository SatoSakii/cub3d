/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:49:43 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/02 20:12:48 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_extended.h"
#include "render.h"
#include <stdio.h>
#include <SDL2/SDL_scancode.h>
#include <math.h>
#include <sys/time.h>

#define MOVE_SPEED 2
#define ROT_SPEED 1

void    move_forward(t_player *player, double delta_time)
{
    player->pos.x += player->dir.x * MOVE_SPEED * delta_time;
    player->pos.y += player->dir.y * MOVE_SPEED * delta_time;
	//check collide;
}

void    move_backward(t_player *player, double delta_time)
{
    player->pos.x -= player->dir.x * MOVE_SPEED * delta_time;
    player->pos.y -= player->dir.y * MOVE_SPEED * delta_time;
}

void    move_right(t_player *player, double delta_time)
{
    player->pos.x += player->plane.x * MOVE_SPEED * delta_time;
    player->pos.y += player->plane.y * MOVE_SPEED * delta_time;
}

void    move_left(t_player *player, double delta_time)
{
    player->pos.x -= player->plane.x * MOVE_SPEED * delta_time;
    player->pos.y -= player->plane.y * MOVE_SPEED * delta_time;
}

void	rotate_left(t_player *player, double delta_time)
{
	double	cos_rot;
	double	sin_rot;
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	cos_rot = cos(-ROT_SPEED * delta_time);
	sin_rot = sin(-ROT_SPEED * delta_time);
	player->dir.x = player->dir.x * cos_rot - player->dir.y * sin_rot;
    player->dir.y = old_dir_x * sin_rot + player->dir.y * cos_rot;
	player->plane.x = player->plane.x * cos_rot - player->plane.y * sin_rot;
    player->plane.y = old_plane_x * sin_rot + player->plane.y * cos_rot;
}

void	rotate_right(t_player *player, double delta_time)
{
	double	cos_rot;
	double	sin_rot;
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	cos_rot = cos(ROT_SPEED * delta_time);
	sin_rot = sin(ROT_SPEED * delta_time);
	player->dir.x = player->dir.x * cos_rot - player->dir.y * sin_rot;
    player->dir.y = old_dir_x * sin_rot + player->dir.y * cos_rot;
	player->plane.x = player->plane.x * cos_rot - player->plane.y * sin_rot;
    player->plane.y = old_plane_x * sin_rot + player->plane.y * cos_rot;
}

double	get_delta_time(void)
{
	static struct timeval	last_ts;
    struct timeval			cur_ts;
	double					delta_time;

	gettimeofday(&cur_ts, NULL);
	delta_time = (cur_ts.tv_sec - last_ts.tv_sec)
			+ (cur_ts.tv_usec - last_ts.tv_usec) / 1000000.0;
	last_ts = cur_ts;
	return (delta_time);
}

void render(void *param)
{
	t_game	*game;
	unsigned int color_ceiling;
	double	delta_time;

	delta_time = get_delta_time();
	game = (t_game *)param;
	if (game->keys.w)
		move_forward(&game->player, delta_time);
	if (game->keys.s)
		move_backward(&game->player, delta_time);
	if (game->keys.a)
		move_left(&game->player, delta_time);
	if (game->keys.d)
		move_right(&game->player, delta_time);
	if (game->keys.left)
		rotate_left(&game->player, delta_time);
	if (game->keys.right)
		rotate_right(&game->player, delta_time);
	color_ceiling = rgb_to_hex(game->ceiling.r, game->ceiling.g, game->ceiling.b);
	mlx_clear_window(game->mlx.mlx, game->mlx.win, (mlx_color){ .rgba = color_ceiling });
	cub_raycasting(game);
}

void key_hook_down(int key, void* param)
{
	t_game	*game;

	game = (t_game *)param;

	if (key == SDL_SCANCODE_ESCAPE)
		mlx_loop_end(game->mlx.mlx);
	else if (key == SDL_SCANCODE_W)
		game->keys.w = 1;
	else if (key == SDL_SCANCODE_S)
		game->keys.s = 1;
	else if (key == SDL_SCANCODE_A)
		game->keys.a = 1;
	else if (key == SDL_SCANCODE_D)
		game->keys.d = 1;
	else if (key == SDL_SCANCODE_LEFT)
		game->keys.left = 1;
	else if (key == SDL_SCANCODE_RIGHT)
		game->keys.right = 1;
}

void	key_hook_release(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;

	if (key == SDL_SCANCODE_W)
		game->keys.w = 0;
	else if (key == SDL_SCANCODE_S)
		game->keys.s = 0;
	else if (key == SDL_SCANCODE_A)
		game->keys.a = 0;
	else if (key == SDL_SCANCODE_D)
		game->keys.d = 0;
	else if (key == SDL_SCANCODE_LEFT)
		game->keys.left = 0;
	else if (key == SDL_SCANCODE_RIGHT)
		game->keys.right = 0;
}

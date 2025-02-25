/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:49:43 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/25 21:07:22 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <SDL2/SDL_scancode.h>
#include <math.h>

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.1

void    move_forward(t_player *player)
{
    player->pos.x += player->dir.x * MOVE_SPEED;
    player->pos.y += player->dir.y * MOVE_SPEED;
	//check collide;
}

void    move_backward(t_player *player)
{
    player->pos.x -= player->dir.x * MOVE_SPEED;
    player->pos.y -= player->dir.y * MOVE_SPEED;
}

void    move_right(t_player *player)
{
    player->pos.x += player->plane.x * MOVE_SPEED;
    player->pos.y += player->plane.y * MOVE_SPEED;
}

void    move_left(t_player *player)
{
    player->pos.x -= player->plane.x * MOVE_SPEED;
    player->pos.y -= player->plane.y * MOVE_SPEED;
}

void	rotate_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cos(-ROT_SPEED) - player->dir.y * sin(-ROT_SPEED);
    player->dir.y = old_dir_x * sin(-ROT_SPEED) + player->dir.y * cos(-ROT_SPEED);
	player->plane.x = player->plane.x * cos(-ROT_SPEED) - player->plane.y * sin(-ROT_SPEED);
    player->plane.y = old_plane_x * sin(-ROT_SPEED) + player->plane.y * cos(-ROT_SPEED);
}

void	rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cos(ROT_SPEED) - player->dir.y * sin(ROT_SPEED);
    player->dir.y = old_dir_x * sin(ROT_SPEED) + player->dir.y * cos(ROT_SPEED);
	player->plane.x = player->plane.x * cos(ROT_SPEED) - player->plane.y * sin(ROT_SPEED);
    player->plane.y = old_plane_x * sin(ROT_SPEED) + player->plane.y * cos(ROT_SPEED);
}

void key_hook(int key, void* param)
{
	t_game	*game;

	game = (t_game *)param;
    if (key == SDL_SCANCODE_ESCAPE)
		mlx_loop_end(game->mlx.mlx);
	else if (key == SDL_SCANCODE_W)
        move_forward(&game->player);
    else if (key == SDL_SCANCODE_S)
        move_backward(&game->player);
    else if (key == SDL_SCANCODE_A)
        move_left(&game->player);
    else if (key == SDL_SCANCODE_D)
        move_right(&game->player);
    else if (key == SDL_SCANCODE_LEFT)
        rotate_left(&game->player);
    else if (key == SDL_SCANCODE_RIGHT)
        rotate_right(&game->player);
    printf("vecX = %f | vecY = %f\ncoX = %f | coY = %f\nplaneX = %f | planeY = %f\n\n", game->player.dir.x, game->player.dir.y, game->player.pos.x, game->player.pos.y, game->player.plane.x, game->player.plane.y);
}

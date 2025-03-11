/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:10:53 by albernar          #+#    #+#             */
/*   Updated: 2025/03/11 21:38:55 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_destroy_wall(t_game *game, t_ray *ray)
{
	ray->raydir.x = game->player.dir.x;
	ray->raydir.y = game->player.dir.y;
	ray->map.x = (int)floor(game->player.pos.x);
	ray->map.y = (int)floor(game->player.pos.y);
	if (ray->raydir.x == 0.0)
		ray->deltadist.x = 1e30;
	else
		ray->deltadist.x = fabs(1.0 / ray->raydir.x);
	if (ray->raydir.y == 0.0)
		ray->deltadist.y = 1e30;
	else
		ray->deltadist.y = fabs(1.0 / ray->raydir.y);
}

void	destroy_wall(t_game *game)
{
	t_ray	ray;
	int		side;
	double	wall_dist;

	init_destroy_wall(game, &ray);
	perform_dda(&ray, game);
	ray.hit = false;
	check_hit(&ray, game, &side);
	if (ray.hit)
	{
		if (side == EAST || side == WEST)
			wall_dist = (ray.sidedist.x - ray.deltadist.x);
		else
			wall_dist = (ray.sidedist.y - ray.deltadist.y);
		if (wall_dist <= DELETE_WALL_DIST && (ray.map.x >= 0
				&& ray.map.x < (int)game->map.width && ray.map.y >= 0
				&& ray.map.y < (int)game->map.height))
		{
			if (game->map.grid[ray.map.y][ray.map.x] == '1')
				game->map.grid[ray.map.y][ray.map.x] = '0';
		}
	}
}

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
	else if (keycode == SDL_SCANCODE_DELETE)
		destroy_wall(game);
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

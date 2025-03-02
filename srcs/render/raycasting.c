/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:27:52 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/02 20:09:27 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_extended.h"
#include "render.h"
#include <math.h>
#include <sys/time.h>
#include <stdio.h>
# define MAX_RAY_DISTANCE 100.0

void draw_vertical_line(mlx_color *pixels, int x, int start, int end)
{
    int line_length;

    if (x < 0 || x >= WINDOW_WIDTH)
        return;
    if (start < 0)
        start = 0;
    if (end >= WINDOW_HEIGHT)
        end = WINDOW_HEIGHT - 1;
    line_length = end - start + 1;
    if (line_length <= 0)
        return;
    for (int i = 0; i < line_length; i++)
        pixels[(start + i) * WINDOW_WIDTH + x].rgba = 0xFF9032FF;
}

void	print_fps(void)
{
    static int				frames = 0;
	static struct timeval	last_ts;
    struct timeval			cur_ts;

    gettimeofday(&cur_ts, NULL);
    frames++;
    double seconds = (cur_ts.tv_sec - last_ts.tv_sec)
            + (cur_ts.tv_usec - last_ts.tv_usec) / 1000000.0;
	printf("FPS: %.2f\n", frames / seconds);
	frames = 0;
	last_ts = cur_ts;
}

unsigned int rgb_to_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

void	fill_floor(mlx_color *pixels, t_game *game)
{
    const unsigned int color_floor = rgb_to_hex(game->floor.r, game->floor.g, game->floor.b);

	for (int i = (WINDOW_WIDTH * (WINDOW_HEIGHT / 2)); i < (WINDOW_WIDTH * WINDOW_HEIGHT); i++)
		pixels[i].rgba = color_floor;
}

void cub_raycasting(t_game *game)
{
    float camera_x, raydir_x, raydir_y, delta_dist_x, delta_dist_y;
    float side_dist_x, side_dist_y, perp_wall_dist;
    int step_x, step_y, map_x, map_y, side, line_height, draw_start, draw_end;
    bool hit;

    mlx_color pixels[WINDOW_WIDTH * WINDOW_HEIGHT] = {0};
    fill_floor(pixels, game);
    float inv_width = 2.0f / (float)WINDOW_WIDTH;
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        camera_x = x * inv_width - 1.0f;
        raydir_x = game->player.dir.x + game->player.plane.x * camera_x;
        raydir_y = game->player.dir.y + game->player.plane.y * camera_x;
        map_x = (int)game->player.pos.x;
        map_y = (int)game->player.pos.y;
        delta_dist_x = fabs(1 / raydir_x);
        delta_dist_y = fabs(1 / raydir_y);
        if (raydir_x < 0)
		{
			step_x = -1;
            side_dist_x = (game->player.pos.x - map_x) * delta_dist_x;
        }
		else
		{
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.pos.x) * delta_dist_x;
        }
        if (raydir_y < 0)
		{
            step_y = -1;
            side_dist_y = (game->player.pos.y - map_y) * delta_dist_y;
        }
		else
		{
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.pos.y) * delta_dist_y;
        }
        hit = false;
        while (!hit)
        {
            if (side_dist_x < side_dist_y)
			{
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
			else
			{
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
			if (map_x < 0 || map_x >= game->map.grid_size || map_y < 0 || map_y >= game->map.grid_size)
            {
                if ((side == 0 ? side_dist_x : side_dist_y) > MAX_RAY_DISTANCE)
                    break ;
            }
			else if (game->map.grid[map_y][map_x] == '1')
                hit = true;
        }
		if (!hit)
			continue;
        perp_wall_dist = (side == 0)
            ? (map_x - game->player.pos.x + (1 - step_x) / 2) / raydir_x
            : (map_y - game->player.pos.y + (1 - step_y) / 2) / raydir_y;
        line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
        draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT - 1;
        draw_vertical_line(pixels, x, draw_start, draw_end);
    }
    mlx_pixel_put_array(game->mlx.mlx, game->mlx.win, 0, 0, pixels, WINDOW_WIDTH * WINDOW_HEIGHT);
    print_fps();
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:27:52 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/27 18:13:49 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "render.h"
#include <math.h>

void draw_vertical_line(t_game *game, int x, int start, int end) {
    for (int y = start; y < end; y++) {
		mlx_pixel_put(game->mlx.mlx, game->mlx.win, x, y, (mlx_color){ .rgba = 0xFF9032FF});
    }
}

void cub_raycasting(t_game *game)
{
    float camera_x, raydir_x, raydir_y, delta_dist_x, delta_dist_y;
    float side_dist_x, side_dist_y, perp_wall_dist;
    int step_x, step_y, map_x, map_y, side, line_height, draw_start, draw_end;
    bool hit;

    for (int x = 0; x < WINDOW_WIDTH; x++) {
        camera_x = 2 * x / (float)WINDOW_WIDTH - 1;
        raydir_x = game->player.dir.x + game->player.plane.x * camera_x;
        raydir_y = game->player.dir.y + game->player.plane.y * camera_x;

        map_x = (int)game->player.pos.x;
        map_y = (int)game->player.pos.y;
        delta_dist_x = fabs(1 / raydir_x);
        delta_dist_y = fabs(1 / raydir_y);

        if (raydir_x < 0) {
            step_x = -1;
            side_dist_x = (game->player.pos.x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.pos.x) * delta_dist_x;
        }
        if (raydir_y < 0) {
            step_y = -1;
            side_dist_y = (game->player.pos.y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.pos.y) * delta_dist_y;
        }
        
        hit = false;
        while (!hit) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (game->map.grid[map_y][map_x] == '1')
                hit = true;
        }

        perp_wall_dist = (side == 0)
            ? (map_x - game->player.pos.x + (1 - step_x) / 2) / raydir_x
            : (map_y - game->player.pos.y + (1 - step_y) / 2) / raydir_y;

        line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
        draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT - 1;

        draw_vertical_line(game, x, draw_start, draw_end);
    }
}

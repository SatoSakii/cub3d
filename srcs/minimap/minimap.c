/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:03:42 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/15 22:22:25 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#define SQUARE_SIZE 10
#define MINIMAP_R 100
#define OFFSET 20

#define PI 3.14159265359

void rotate_point(float *x, float *y, float cx, float cy, float theta)
{
    float dx = *x - cx;
    float dy = *y - cy;
    *x = cx + (dx * cos(-theta) - dy * sin(-theta));
    *y = cy + (dx * sin(-theta) + dy * cos(-theta));

}

static void draw_minimap_background(t_game *game, int minimap_x, int minimap_y)
{
    int dx, dy;
    for (dy = -MINIMAP_R; dy <= MINIMAP_R; dy++)
    {
        for (dx = -MINIMAP_R; dx <= MINIMAP_R; dx++)
        {
            if (dx * dx + dy * dy <= MINIMAP_R * MINIMAP_R)
            {
                int index = (minimap_y + dy) * WINDOW_WIDTH + (minimap_x + dx);
                if (index >= 0 && index < WINDOW_WIDTH * WINDOW_HEIGHT)
                    game->scene[index].rgba = 0x000000FF;
            }
        }
    }
}
static void draw_square(t_game *game, float x, float y, bool flag, float theta)
{
    int tmp_x, tmp_y;
    int width = WINDOW_WIDTH;
    int index;
	__attribute__((unused))
	float	xdx, xdy;
	__attribute__((unused))
	float	ydx, ydy;

    tmp_x = 0;
	xdx = 0;
	xdy = 0;
	ydx = 0;
	ydy = 0;
 //   index = (y + xdy + ydy) * width + (x + xdx + ydx);
	(void)theta;
    while (tmp_x < SQUARE_SIZE)
    {
        tmp_y = 0;
	//	xdx += cos(theta);
	//	xdy += sin(theta);
	//	printf("xdx = %f | xdy = %f\n", xdx, xdy);
        while (tmp_y < SQUARE_SIZE)
        {
			//ydx += sin(theta);
			//ydy += cos(theta);
			//
		//	x = cx + (dx * cos(-theta) - dy * sin(-theta));
		//	y = cy + (dx * sin(-theta) + dy * cos(-theta));
         //   index = (y + (tmp_x * sin(-theta)) + (tmp_y * cos(-theta))) * width + (x + (tmp_x * cos(-theta)) - tmp_y * sin(-theta));
			size_t	px = (x + tmp_x * cos(-theta) - tmp_y * sin(-theta));
			size_t	py = (y + tmp_x * sin(-theta) + tmp_y * cos(-theta));
			index = py  * width + px;
			//index = (y + tmp_y * cos(-theta)) * width + (x + tmp_x * sin(-theta));
            if (index < 0 || index >= WINDOW_WIDTH * WINDOW_HEIGHT)
                return;
            if (flag)
                game->scene[index].rgba = 0x555C54FF;
            else
                game->scene[index].rgba = 0xF6F6DAFF;
            tmp_y++;
        }
        tmp_x++;
    }
}

static void draw_player(t_game *game, int map_x, int map_y)
{
    float player_x = map_x + MINIMAP_R;
    float player_y = map_y + MINIMAP_R;
    int radius = SQUARE_SIZE / 4;
    int dx, dy, index;

    dx = -radius;
    while (dx <= radius)
    {
        dy = -radius;
        while (dy <= radius)
        {
            if (dx * dx + dy * dy <= radius * radius)
            {
                index = ((player_y + dy)) * WINDOW_WIDTH + ((player_x + dx));
                if (index >= 0 && index < WINDOW_WIDTH * WINDOW_HEIGHT)
                    game->scene[index].rgba = 0xFF00FFFF;
            }
            dy++;
        }
        dx++;
    }
}

void print_minimap(t_game *game, int pos)
{
    int origin_x = game->player.pos.x * SQUARE_SIZE - MINIMAP_R;
    int origin_y = game->player.pos.y * SQUARE_SIZE - MINIMAP_R;
    int map_x, map_y;

    if (pos & 0b1000)
        map_y = OFFSET;
    else
        map_y = WINDOW_HEIGHT - ((game->map.height * SQUARE_SIZE) - MINIMAP_R) + OFFSET;

    if (pos & 0b0010)
        map_x = OFFSET;
    else
        map_x = WINDOW_WIDTH - ((game->map.width * SQUARE_SIZE) - MINIMAP_R) + OFFSET;
    draw_minimap_background(game, map_x + MINIMAP_R, map_y + MINIMAP_R);
	float player_angle = atan2f(game->player.dir.y, game->player.dir.x);
    for (size_t y = 0; y < game->map.height; y++)
    {
        for (size_t x = 0; x < game->map.width; x++)
        {
            float mx = x * SQUARE_SIZE + map_x - origin_x;
            float my = y * SQUARE_SIZE + map_y - origin_y;
			rotate_point(&mx, &my, map_x + MINIMAP_R, map_y + MINIMAP_R, player_angle);
            if ((mx - (map_x + MINIMAP_R)) * (mx - (map_x + MINIMAP_R)) +
                (my - (map_y + MINIMAP_R)) * (my - (map_y + MINIMAP_R)) <= MINIMAP_R * MINIMAP_R)
            {
                bool is_wall = (game->map.grid[y][x] == '1');
                draw_square(game, mx, my, is_wall, player_angle);
            }
        }
    }
    draw_player(game, map_x, map_y);
}


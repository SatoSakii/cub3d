/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:57:48 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/26 14:36:07 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

#define PLAYER_SIZE 10

void draw_line(t_game *game, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_pixel_put(game->mlx.mlx, game->mlx.win, x0, y0, (mlx_color){ .rgba = 0x00FF00FF });
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
void draw_player_direction(t_game *game)
{
    int arrow_length = 10;
    
    // Décale légèrement la position du joueur pour dessiner la ligne en dehors du carré
    int offset = PLAYER_SIZE / 2 - 1;  // Décalage d'une petite valeur (par exemple, 1 pixel)
    
    // Calculer la position de départ de la ligne (juste à l'extérieur du carré)
    int start_x = game->player.pos.x + game->player.dir.x * offset;
    int start_y = game->player.pos.y + game->player.dir.y * offset;
    
    // Calculer la position de fin de la ligne (en fonction de la direction et de la longueur de la flèche)
    int end_x = start_x + game->player.dir.x * arrow_length;
    int end_y = start_y + game->player.dir.y * arrow_length;

    draw_line(game, start_x, start_y, end_x, end_y);
}

void	draw_player(t_game *game)
{
	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		for (int j = 0; j < PLAYER_SIZE; j++)
			mlx_pixel_put(game->mlx.mlx, game->mlx.win, game->player.pos.x + i, game->player.pos.y + j, (mlx_color){ .rgba = 0x0000FFFF });
	}
	draw_player_direction(game);
}

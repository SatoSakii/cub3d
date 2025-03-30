/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:57:08 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 14:34:04 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

static int	manage_recursion(char **map, t_floodfill *floodfill, int *x, int *y)
{
	if (floodfill->total_reached)
		return (PROCESS_ERR);
	if (floodfill->total == 1000)
	{
		floodfill->total_reached = true;
		floodfill->total = 0;
		return (PROCESS_ERR);
	}
	if (floodfill->total == 0 && floodfill->save.x != -1
		&& floodfill->save.y != -1)
	{
		*x = floodfill->save.x;
		*y = floodfill->save.y;
		map[*y][*x] = '0';
	}
	floodfill->total++;
	return (PROCESS_OK);
}

static int	flood_fill(int x, int y, char **map, t_floodfill *floodfill)
{
	if (manage_recursion(map, floodfill, &x, &y))
		return (PROCESS_ERR);
	if (x < 0 || y < 0 || y >= (int)ft_strscount(map)
		|| x >= (int)ft_strlen(map[y]))
	{
		floodfill->error = true;
		return (PROCESS_ERR);
	}
	else if (map[y][x] == '1' || map[y][x] == '2')
		return (PROCESS_OK);
	else if (map[y][x] == '0')
	{
		floodfill->save.x = x;
		floodfill->save.y = y;
	}
	map[y][x] = '1';
	return (flood_fill(x + 1, y, map, floodfill)
		+ flood_fill(x - 1, y, map, floodfill)
		+ flood_fill(x, y + 1, map, floodfill)
		+ flood_fill(x, y - 1, map, floodfill));
}

static int	managed_flood_fill(int player_x, int player_y,
	char **map, t_floodfill *floodfill)
{
	int	ret;

	ret = PROCESS_ERR;
	while (ret != PROCESS_OK)
	{
		ret = flood_fill(player_x, player_y, map, floodfill);
		floodfill->total_reached = false;
		if (floodfill->error)
			break ;
	}
	return (ret);
}

int	map_floodfill(t_game *game, t_error_ctx *ctx)
{
	t_floodfill	floodfill;
	char		**map_copy;
	int			x;
	int			y;

	floodfill = (t_floodfill){0, {-1, -1}, false, false};
	apply_ctx(ctx, -1, -1);
	ctx->line_content = NULL;
	map_copy = copy_map(ctx, game->map.grid);
	if (!map_copy)
		return (PROCESS_ERR);
	while (find_next_zero(map_copy, &x, &y))
	{
		if (managed_flood_fill(x, y, map_copy, &floodfill) != PROCESS_OK
			|| floodfill.error)
		{
			ft_free2d((void **)map_copy);
			throw_err(ERR_FLOODFILL, ctx);
			return (PROCESS_ERR);
		}
	}
	ft_free2d((void **)map_copy);
	return (PROCESS_OK);
}

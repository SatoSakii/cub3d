/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:01:53 by albernar          #+#    #+#             */
/*   Updated: 2025/02/25 14:35:52 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_file(int argc, char **argv, t_error_ctx *ctx, t_game *game)
{
	int	err;
	int	fd;

	err = validate_argument_count(argc, argv, ctx);
	if (err)
		return (PROCESS_ERR);
	err = validate_file_extension(ctx);
	if (err)
		return (PROCESS_ERR);
	fd = validate_open_file(ctx);
	if (fd == PROCESS_ERR)
		return (PROCESS_ERR);
	err = parse_data(fd, ctx, game);
	if (err == PROCESS_ERR)
	{
		close(fd);
		return (PROCESS_ERR);
	}
	err = parse_map(fd, ctx, game);
	close(fd);
	return (err);
}

int	main(int argc, char **argv)
{
	t_error_ctx	ctx;
	t_game		game;

	game = (t_game){0};
	ctx = (t_error_ctx){0};
	ft_memset(&game.ceiling, -1, sizeof(game.ceiling));
	ft_memset(&game.floor, -1, sizeof(game.floor));
	if (parse_file(argc, argv, &ctx, &game) == PROCESS_ERR)
	{
		free_game(&game);
		return (1);
	}
	ft_dprintf(2, "parsing success\n");
	ft_dprintf(2, "NO Tex : %s\n", game.no.path);
	ft_dprintf(2, "SO Tex : %s\n", game.so.path);
	ft_dprintf(2, "WE Tex : %s\n", game.we.path);
	ft_dprintf(2, "EA Tex : %s\n", game.ea.path);
	ft_dprintf(2, "Floor : (%d, %d, %d)\n", game.floor.r,
		game.floor.g, game.floor.b);
	ft_dprintf(2, "Ceiling : (%d, %d, %d)\n\n", game.ceiling.r,
		game.ceiling.g, game.ceiling.b);
	for (int i = 0; game.map.grid[i]; i++)
		ft_printf("%s", game.map.grid[i]);
	free_game(&game);
	return (0);
}

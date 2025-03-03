/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:01:53 by albernar          #+#    #+#             */
/*   Updated: 2025/03/02 20:05:36 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_extended.h"
#include "render.h"

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

void	put_textures(t_game *game)
{
	int			img_width;
	int			img_height;
	mlx_image	img = mlx_new_image_from_file(game->mlx.mlx, "textures/wood.png", &img_width, &img_height);
    mlx_color   *pixel_dest = malloc(sizeof(mlx_color) * img_width * img_height);

    mlx_get_image_region(game->mlx.mlx, img, 0, 0, img_width, img_height, pixel_dest);
    game->no.width = img_width;
    game->no.height = img_height;
	game->no.img = pixel_dest; 
}

int	main(int argc, char **argv)
{
	t_error_ctx	ctx;
	t_game		game;

	game = (t_game){0};
	game.keys = (t_keys){0};
	ctx = (t_error_ctx){0};
	ft_memset(&game.ceiling, -1, sizeof(game.ceiling));
	ft_memset(&game.floor, -1, sizeof(game.floor));
	if (parse_file(argc, argv, &ctx, &game) == PROCESS_ERR)
	{
		free_game(&game);
		return (1);
	}
	init_mlx(&game.mlx);
	put_textures(&game);
	mlx_on_event(game.mlx.mlx, game.mlx.win, MLX_KEYDOWN, key_hook_down, &game);
	mlx_on_event(game.mlx.mlx, game.mlx.win, MLX_KEYUP, key_hook_release, &game);
	mlx_add_loop_hook(game.mlx.mlx, render, &game);
	mlx_loop(game.mlx.mlx);
	mlx_destroy_window(game.mlx.mlx, game.mlx.win);
	mlx_destroy_context(game.mlx.mlx);
	free_game(&game);
	return (0);
}

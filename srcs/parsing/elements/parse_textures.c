/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:07:16 by albernar          #+#    #+#             */
/*   Updated: 2025/02/25 14:31:41 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_tex_path(char *path, t_textures *tx, t_error_ctx *ctx)
{
	int	fd;
	int	len;

	len = ft_strlen(path) - 1;
	path[len] = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		path[len] = '\n';
		apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
		if (errno == EACCES)
		{
			apply_ctx(ctx, ft_strlen(path) - 1,
				ft_strlen(ctx->line_content) - ft_strlen(path));
			throw_err(ERR_PERMISSION_DENIED, ctx);
		}
		else
			throw_err(ERR_INVALID_TEXTURE, ctx);
		return (-1);
	}
	tx->path = path;
	tx->addr = ctx->line_content;
	close(fd);
	return (1);
}

int	handle_texture(char *line, t_error_ctx *ctx, t_game *g)
{
	int					i;
	const char			*ids[4] = {"NO", "SO", "WE", "EA"};
	const t_textures	*textures[4] = {&g->no, &g->so, &g->we, &g->ea};

	i = -1;
	ctx->line_content = line;
	skip_spaces(&line);
	while (++i < 4)
	{
		if (!ft_strncmp(line, ids[i], 2))
		{
			line += 2;
			if (info_hasspace(line, ctx) == PROCESS_ERR)
				return (PROCESS_ERR);
			skip_spaces(&line);
			if (textures[i]->path)
			{
				apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
				throw_err(ERR_DUPLICATE_TEXTURE, ctx);
				return (PROCESS_ERR);
			}
			return (validate_tex_path(line, (t_textures *)textures[i], ctx));
		}
	}
	return (PROCESS_OK);
}

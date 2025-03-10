/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:34:32 by albernar          #+#    #+#             */
/*   Updated: 2025/03/07 01:03:23 by albernar         ###   ########.fr       */
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

int	handle_texture(char *line, t_error_ctx *ctx)
{
	int					i;
	const t_event		*e = get_events();
	const int			e_len = get_event_len((t_event *)e);

	i = -1;
	ctx->line_content = line;
	skip_spaces(&line);
	while (++i < e_len)
	{
		if (!ft_strncmp(line, e[i].name, TEX_LEN) && ft_isspace(line[TEX_LEN])
			&& e[i].type == TEXTURE)
		{
			line += TEX_LEN;
			if (info_hasspace(&line, ctx, (t_event *)&e[i]) == PROCESS_ERR)
				return (PROCESS_ERR);
			if (((t_textures *)(e[i].data))->path)
			{
				apply_ctx(ctx, ft_strlen(ctx->line_content) - 1, 0);
				throw_err(ERR_DUPLICATE_TEXTURE, ctx);
				return (PROCESS_ERR);
			}
			return (validate_tex_path(line, ((t_textures *)(e[i].data)), ctx));
		}
	}
	return (PROCESS_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:59:06 by albernar          #+#    #+#             */
/*   Updated: 2025/02/23 19:06:04 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_args_len(char **argv)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (argv[i])
	{
		len += ft_strlen(argv[i]);
		i++;
	}
	return (len + i - 1);
}

int	validate_argument_count(int argc, char **argv, t_error_ctx *ctx)
{
	ctx->args = argv;
	ctx->executable = argv[0];
	if (argc < 2)
	{
		ctx->error_pos = ft_strlen(argv[0]);
		ctx->error_len = 1;
		throw_err(ERR_NOT_ENOUGH_ARGS, ctx);
		return (PROCESS_ERR);
	}
	ctx->filename = argv[1];
	if (argc > 2)
	{
		ctx->error_pos = ft_strlen(argv[0]) + ft_strlen(argv[1]) + 1;
		ctx->error_len = get_args_len(argv) - ft_strlen(argv[0])
			- ft_strlen(argv[1]) - 1;
		throw_err(ERR_TOO_MANY_ARGS, ctx);
		return (PROCESS_ERR);
	}
	return (PROCESS_OK);
}

int	validate_file_extension(t_error_ctx *ctx)
{
	char	*ext;

	ext = ft_strrchr(ctx->filename, '.');
	if (!ext)
	{
		ctx->error_pos = ft_strlen(ctx->executable) + ft_strlen(ctx->filename)
			+ 1;
		ctx->error_len = 1;
		throw_err(ERR_NO_FILE_TYPE, ctx);
		return (PROCESS_ERR);
	}
	else if (ft_strncmp(ext, ".cub", 5))
	{
		ctx->error_pos = ft_strlen(ctx->executable) + ft_strlen(ctx->filename)
			+ 1 - ft_strlen(ext);
		ctx->error_len = ft_strlen(ext);
		throw_err(ERR_INVALID_EXTENSION, ctx);
		return (PROCESS_ERR);
	}
	return (PROCESS_OK);
}

int	validate_open_file(t_error_ctx *ctx)
{
	int	fd;

	fd = open(ctx->filename, O_RDONLY);
	if (fd < 0)
	{
		ctx->error_pos = ft_strlen(ctx->executable) + 1;
		ctx->error_len = ft_strlen(ctx->filename);
		if (errno == ENOENT)
			throw_err(ERR_NO_FILE_FOUND, ctx);
		else if (errno == EACCES)
			throw_err(ERR_PERMISSION_DENIED, ctx);
		else
			throw_err(ERR_INVALID_FILE, ctx);
		return (PROCESS_ERR);
	}
	return (fd);
}

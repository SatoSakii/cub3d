/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:47:06 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 18:11:44 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

static void	replace_tab(char **tmp)
{
	int	i;

	i = 0;
	while ((*tmp)[i])
	{
		if ((*tmp)[i] == '\t')
			(*tmp)[i] = ' ';
		i++;
	}
}

static void	print_args(char **argv, t_error_ctx *ctx)
{
	int	i;

	i = 0;
	if (ctx->error_len == -1 || ctx->error_pos == -1)
		return ;
	while (argv[i])
	{
		ft_dprintf(2, "%s", argv[i]);
		if (argv[i + 1])
			ft_dprintf(2, " ");
		i++;
	}
	ft_dprintf(2, "\n");
}

static void	print_underline(t_error error, t_error_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->error_pos)
	{
		ft_dprintf(2, " ");
		i++;
	}
	if (ctx->line_content)
		ft_dprintf(2, "        ");
	i = 0;
	while (i < ctx->error_len)
	{
		ft_dprintf(2, RED "^");
		i++;
	}
	if (ctx->error_len != -1 || ctx->error_pos != -1)
		ft_dprintf(2, RESET " <%c%s>\n",
			ERR_MSG[error] + 32, &ERR_MSG[error] + 1);
}

void	throw_err(t_error error, t_error_ctx *ctx)
{
	char	*tmp;

	ft_dprintf(2, RED "❌ Error" RESET ": %s.\n", &ERR_MSG[error]);
	if (!ctx->line_content)
		print_args(ctx->args, ctx);
	else
	{
		tmp = ctx->line_content;
		replace_tab(&tmp);
		if (error == ERR_MISSING_INFO || error == ERR_NO_PLY)
			ft_dprintf(2, "In file : %s (line Unknown)\n", ctx->filename);
		else
			ft_dprintf(2, "In file : %s (line %d)\n", ctx->filename,
				ctx->line_num);
		ft_dprintf(2, "        %s", ctx->line_content);
		if (error == ERR_MISSING_INFO || error == ERR_NO_PLY)
			ft_dprintf(2, "\n");
		if (ctx->line_content && error < ERR_MISSING_INFO)
			free(ctx->line_content);
	}
	print_underline(error, ctx);
}

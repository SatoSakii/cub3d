/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ctx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:17 by albernar          #+#    #+#             */
/*   Updated: 2025/02/21 15:10:01 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_ctx(t_error_ctx *ctx, int error_len, int error_pos)
{
	ctx->error_len = error_len;
	ctx->error_pos = error_pos;
}

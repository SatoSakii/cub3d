/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ctx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:17 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 18:11:44 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

void	apply_ctx(t_error_ctx *ctx, int error_len, int error_pos)
{
	ctx->error_len = error_len;
	ctx->error_pos = error_pos;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:08:57 by albernar          #+#    #+#             */
/*   Updated: 2025/03/14 18:11:30 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

t_mlx_funcs	*get_mlx_funcs(void)
{
	static t_mlx_funcs	funcs;

	return (&funcs);
}

t_vulkan_funcs	*get_vulkan_funcs(void)
{
	static t_vulkan_funcs	funcs;

	return (&funcs);
}

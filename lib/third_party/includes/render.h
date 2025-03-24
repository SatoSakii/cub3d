/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:11:33 by albernar          #+#    #+#             */
/*   Updated: 2025/03/18 19:16:28 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "loader.h"
# include "vulkan_manager.h"
# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# include "cimgui.h"
# include "cimgui_impl.h"
# include "cub3d.h"

typedef struct s_mlx	t_mlx;

void	init_renderer(t_mlx *mlx);
void	destroy_renderer(t_mlx *mlx);
void	begin_render(VkCommandBuffer cmd, void *param);

#endif
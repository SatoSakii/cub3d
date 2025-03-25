/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vk_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:11:33 by albernar          #+#    #+#             */
/*   Updated: 2025/03/25 02:37:38 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_RENDER_H
# define VK_RENDER_H
# include "loader.h"
# include "vulkan_manager.h"
# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# include "cimgui.h"
# include "cimgui_impl.h"
# include "cub3d.h"

typedef struct s_mlx	t_mlx;

void	draw_window(t_game *game, t_mlx *mlx);
void	init_renderer(t_mlx *mlx);
void	destroy_renderer(t_mlx *mlx);
void	begin_render(VkCommandBuffer cmd, void *param);

#endif
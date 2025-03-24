/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:52:55 by albernar          #+#    #+#             */
/*   Updated: 2025/03/14 19:35:56 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VULKAN_MANAGER_H
# define VULKAN_MANAGER_H
# include <mlx.h>
# include <mlx_extended.h>
# include <vulkan/vulkan_core.h>

VkDescriptorPool	vulkan_create_descriptor_pool(mlx_context mlx);
VkRenderPass		vulkan_create_render_pass(mlx_context mlx, mlx_window win);
VkFramebuffer		*vulkan_create_frame_buffers(mlx_context mlx,
						mlx_window win, VkRenderPass renderpass);
void				vulkan_destroy_frame_buffers(mlx_context mlx,
						mlx_window win, VkFramebuffer *framebuffer);

#endif
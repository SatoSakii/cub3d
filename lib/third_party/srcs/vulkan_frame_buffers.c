/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan_frame_buffers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:46:24 by albernar          #+#    #+#             */
/*   Updated: 2025/03/14 18:11:30 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "vulkan_manager.h"

static VkFramebufferCreateInfo	init_framebuffer_create_info(mlx_context mlx,
	mlx_window win, VkRenderPass renderpass, unsigned int i)
{
	VkFramebufferCreateInfo	framebuffer_create_info;
	const VkExtent2D		extent
		= get_mlx_funcs()->mlx_get_vk_swapchain_extent(mlx, win);
	VkImageView				view;

	view = get_mlx_funcs()->mlx_get_vk_swapchain_image_view(mlx, win, i);
	framebuffer_create_info = (VkFramebufferCreateInfo){0};
	framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebuffer_create_info.attachmentCount = 1;
	framebuffer_create_info.pAttachments = &view;
	framebuffer_create_info.renderPass = renderpass;
	framebuffer_create_info.layers = 1;
	framebuffer_create_info.width = extent.width;
	framebuffer_create_info.height = extent.height;
	return (framebuffer_create_info);
}

VkFramebuffer	*vulkan_create_frame_buffers(mlx_context mlx,
	mlx_window win, VkRenderPass renderpass)
{
	const t_vulkan_funcs	*vulkan_funcs = get_vulkan_funcs();
	const VkDevice			device = get_mlx_funcs()->mlx_get_vk_device(mlx);
	const unsigned int		image_count
		= get_mlx_funcs()->mlx_get_vk_swapchain_image_count(mlx, win);
	VkFramebuffer			*framebuffers;
	unsigned int			i;

	framebuffers = malloc(sizeof(VkFramebuffer) * image_count);
	if (!framebuffers)
		return (NULL);
	i = -1;
	while (++i < image_count)
	{
		vulkan_funcs->vk_create_frame_buffer(
			device, (VkFramebufferCreateInfo[])
			{init_framebuffer_create_info(mlx, win, renderpass, i)},
			NULL, &framebuffers[i]);
	}
	return (framebuffers);
}

void	vulkan_destroy_frame_buffers(mlx_context mlx,
	mlx_window win, VkFramebuffer *framebuffer)
{
	const t_vulkan_funcs	*vulkan_funcs = get_vulkan_funcs();
	const unsigned int		image_count
		= get_mlx_funcs()->mlx_get_vk_swapchain_image_count(mlx, win);
	VkDevice				device;
	unsigned int			i;

	device = get_mlx_funcs()->mlx_get_vk_device(mlx);
	vulkan_funcs->vk_device_wait_idle(device);
	i = -1;
	while (++i < image_count)
		vulkan_funcs->vk_destroy_frame_buffer(device, framebuffer[i], NULL);
	free(framebuffer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan_render_pass.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:06:59 by albernar          #+#    #+#             */
/*   Updated: 2025/03/25 03:10:44 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "vulkan_manager.h"

static VkAttachmentReference	create_color_attachment_reference(void)
{
	VkAttachmentReference	color_reference;

	color_reference = (VkAttachmentReference){0};
	color_reference.attachment = 0;
	color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	return (color_reference);
}

static VkAttachmentDescription	init_render_pass_attachment(mlx_context mlx,
	mlx_window win)
{
	const t_mlx_funcs		*mlx_funcs = get_mlx_funcs();
	VkAttachmentDescription	attachment;

	attachment = (VkAttachmentDescription){0};
	attachment.format = mlx_funcs->mlx_get_vk_swapchain_format(mlx, win);
	attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	attachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
	attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
	attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	return (attachment);
}

VkRenderPass	vulkan_create_render_pass(mlx_context mlx, mlx_window win)
{
	const t_vulkan_funcs	*vulkan_funcs = get_vulkan_funcs();
	VkSubpassDescription	subpass;
	VkRenderPass			renderpass;
	VkRenderPassCreateInfo	renderpass_info;

	subpass = (VkSubpassDescription){0};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = (VkAttachmentReference[])
	{create_color_attachment_reference()};
	renderpass_info = (VkRenderPassCreateInfo){0};
	renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderpass_info.attachmentCount = 1;
	renderpass_info.pAttachments = (VkAttachmentDescription[])
	{init_render_pass_attachment(mlx, win)};
	renderpass_info.subpassCount = 1;
	renderpass_info.pSubpasses = &subpass;
	vulkan_funcs->vk_create_render_pass(get_mlx_funcs()->mlx_get_vk_device(mlx),
		&renderpass_info, NULL, &renderpass);
	return (renderpass);
}

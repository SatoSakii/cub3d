/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:11:04 by albernar          #+#    #+#             */
/*   Updated: 2025/03/18 19:15:56 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <SDL2/SDL.h>

static void	vk_render(t_game *game, VkExtent2D swapchain_extent,
	VkCommandBuffer cmd, t_mlx_funcs *mlx_funcs)
{
	ImDrawData				*draw_data;
	VkRenderPassBeginInfo	info;
	const t_vulkan_funcs	*vulkan_funcs = get_vulkan_funcs();
	t_mlx					*mlx;

	mlx = &game->mlx;
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	igNewFrame();
	draw_window(game, mlx);
	igRender();
	draw_data = igGetDrawData();
	info = (VkRenderPassBeginInfo){0};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	info.renderPass = mlx->render.renderpass;
	info.framebuffer = mlx->render.framebuffers[
		mlx_funcs->mlx_get_current_vk_swapchain_image_idx(mlx->ctx, mlx->win)];
	info.renderArea.extent.width = swapchain_extent.width;
	info.renderArea.extent.height = swapchain_extent.height;
	vulkan_funcs->vk_cmd_begin_render_pass(cmd,
		&info, VK_SUBPASS_CONTENTS_INLINE);
	ImGui_ImplVulkan_RenderDrawData(draw_data, cmd, VK_NULL_HANDLE);
	vulkan_funcs->vk_cmd_end_render_pass(cmd);
}

void	begin_render(VkCommandBuffer cmd, void *param)
{
	const t_vulkan_funcs	*vulkan_funcs = get_vulkan_funcs();
	const t_mlx_funcs		*mlx_funcs = get_mlx_funcs();
	t_game					*game;
	t_mlx					*mlx;
	VkExtent2D				swapchain_extent;

	game = (t_game *)param;
	mlx = &game->mlx;
	swapchain_extent = mlx_funcs->mlx_get_vk_swapchain_extent(mlx->ctx,
			mlx->win);
	if (swapchain_extent.width != mlx->render.swapchain_extent.width
		|| swapchain_extent.height != mlx->render.swapchain_extent.height)
	{
		mlx->render.swapchain_extent = swapchain_extent;
		vulkan_destroy_frame_buffers(mlx->ctx, mlx->win,
			mlx->render.framebuffers);
		vulkan_funcs->vk_destroy_render_pass(mlx_funcs->mlx_get_vk_device
			(mlx->ctx), mlx->render.renderpass, NULL);
		mlx->render.renderpass = vulkan_create_render_pass(mlx->ctx, mlx->win);
		mlx->render.framebuffers = vulkan_create_frame_buffers(mlx->ctx,
				mlx->win, mlx->render.renderpass);
	}
	vk_render(game, swapchain_extent, cmd, (t_mlx_funcs *)mlx_funcs);
}

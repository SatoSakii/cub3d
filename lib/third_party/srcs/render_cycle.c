/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:09:08 by albernar          #+#    #+#             */
/*   Updated: 2025/03/14 19:19:35 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	imgui_init_vulkan(t_mlx *mlx, VkSurfaceCapabilitiesKHR capabilities,
	t_mlx_funcs *mlx_funcs)
{
	ImGui_ImplVulkan_InitInfo	init_info;

	ImGui_ImplSDL2_InitForVulkan((SDL_Window *)mlx_funcs->mlx_get_window_handle
		(mlx->ctx, mlx->win));
	init_info = (ImGui_ImplVulkan_InitInfo){0};
	init_info.Instance = mlx->render.instance;
	init_info.PhysicalDevice = mlx->render.physical_device;
	init_info.Device = mlx->render.device;
	init_info.QueueFamily
		= mlx_funcs->mlx_get_vk_graphics_queue_family(mlx->ctx);
	init_info.Queue = mlx_funcs->mlx_get_vk_graphics_queue(mlx->ctx);
	init_info.DescriptorPool = mlx->render.pool;
	init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
	init_info.MinImageCount = capabilities.minImageCount;
	init_info.ImageCount
		= mlx_funcs->mlx_get_vk_swapchain_image_count(mlx->ctx, mlx->win);
	init_info.RenderPass = mlx->render.renderpass;
	ImGui_ImplVulkan_Init(&init_info);
	mlx->render.swapchain_extent
		= mlx_funcs->mlx_get_vk_swapchain_extent(mlx->ctx, mlx->win);
	mlx->render.framebuffers = vulkan_create_frame_buffers(mlx->ctx,
			mlx->win, mlx->render.renderpass);
}

void	init_renderer(t_mlx *mlx)
{
	const t_vulkan_funcs		*vulkan_funcs = get_vulkan_funcs();
	const t_mlx_funcs			*mlx_funcs = get_mlx_funcs();
	ImGuiContext				*ctx;
	VkSurfaceCapabilitiesKHR	capabilities;

	load_mlx_bindings(mlx->ctx, (t_mlx_funcs *)mlx_funcs);
	load_vulkan_bindings(mlx->ctx, (t_mlx_funcs *)mlx_funcs,
		(t_vulkan_funcs *)vulkan_funcs);
	mlx_funcs->mlx_set_sdl_input_hook(mlx->ctx,
		(t_sdl_hook)ImGui_ImplSDL2_ProcessEvent);
	ctx = igCreateContext(NULL);
	igGetIO()->IniFilename = NULL;
	mlx->render.instance = mlx_funcs->mlx_get_vk_instance(mlx->ctx);
	mlx->render.physical_device
		= mlx_funcs->mlx_get_vk_physical_device(mlx->ctx);
	mlx->render.device = mlx_funcs->mlx_get_vk_device(mlx->ctx);
	mlx->render.pool = vulkan_create_descriptor_pool(mlx->ctx);
	mlx->render.renderpass = vulkan_create_render_pass(mlx->ctx, mlx->win);
	ImGui_ImplVulkan_LoadFunctions(imgui_load_vulkan, mlx->render.instance);
	capabilities = (VkSurfaceCapabilitiesKHR){0};
	vulkan_funcs->vk_get_phsic_dvice_surface_cap_khr
		(mlx->render.physical_device,
		mlx_funcs->mlx_get_vk_surface(mlx->ctx, mlx->win), &capabilities);
	imgui_init_vulkan(mlx, capabilities, (t_mlx_funcs *)mlx_funcs);
}

void	destroy_renderer(t_mlx *mlx)
{
	const t_vulkan_funcs		*vulkan_funcs = get_vulkan_funcs();

	vulkan_destroy_frame_buffers(mlx->ctx, mlx->win, mlx->render.framebuffers);
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	igDestroyContext(igGetCurrentContext());
	vulkan_funcs->vk_destroy_descriptor_pool(mlx->render.device,
		mlx->render.pool, NULL);
	vulkan_funcs->vk_destroy_render_pass(mlx->render.device,
		mlx->render.renderpass, NULL);
}

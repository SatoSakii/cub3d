/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:18:30 by albernar          #+#    #+#             */
/*   Updated: 2025/03/14 18:30:51 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

T_VK_VOID_FUNC	imgui_load_vulkan(const char *name, void *data)
{
	const t_vulkan_funcs	*vk_funcs = get_vulkan_funcs();

	if (strcmp(name, "vkCmdBeginRenderPass") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_cmd_begin_render_pass);
	if (strcmp(name, "vkCmdEndRenderPass") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_cmd_end_render_pass);
	if (strcmp(name, "vkCreateDescriptorPool") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_create_descriptor_pool);
	if (strcmp(name, "vkCreateFramebuffer") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_create_frame_buffer);
	if (strcmp(name, "vkCreateRenderPass") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_create_render_pass);
	if (strcmp(name, "vkDestroyFramebuffer") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_destroy_frame_buffer);
	if (strcmp(name, "vkDestroyRenderPass") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_destroy_render_pass);
	if (strcmp(name, "vkDeviceWaitIdle") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_device_wait_idle);
	if (strcmp(name, "vkGetInstanceProcAddr") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_get_instance_proc_addr);
	if (strcmp(name, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_get_phsic_dvice_surface_cap_khr);
	if (strcmp(name, "vkDestroyDescriptorPool") == 0)
		return ((T_VK_VOID_FUNC)vk_funcs->vk_destroy_descriptor_pool);
	return (vk_funcs->vk_get_instance_proc_addr((VkInstance)data, name));
}

void	load_utils_mlx_bindings(mlx_context mlx, t_mlx_funcs *mlx_funcs)
{
	mlx_funcs->mlx_get_vk_graphics_queue
		= (t_mlx_get_vk_graphics_queue)
		mlx_get_proc_addr(mlx, "mlx_get_vk_graphics_queue");
	mlx_funcs->mlx_get_vk_graphics_queue_family
		= (t_mlx_get_vk_graphics_queue_family)
		mlx_get_proc_addr(mlx, "mlx_get_vk_graphics_queue_family");
	mlx_funcs->mlx_get_vk_instance
		= (t_mlx_get_vk_instance)
		mlx_get_proc_addr(mlx, "mlx_get_vk_instance");
	mlx_funcs->mlx_get_vk_physical_device
		= (t_mlx_get_vk_physical_device)
		mlx_get_proc_addr(mlx, "mlx_get_vk_physical_device");
	mlx_funcs->mlx_get_vk_surface
		= (t_mlx_get_vk_surface)
		mlx_get_proc_addr(mlx, "mlx_get_vk_surface");
	mlx_funcs->mlx_get_window_handle
		= (t_mlx_get_window_handle)
		mlx_get_proc_addr(mlx, "mlx_get_window_handle");
	mlx_funcs->mlx_set_sdl_input_hook
		= (t_mlx_set_sdl_input_hook)
		mlx_get_proc_addr(mlx, "mlx_set_sdl_input_hook");
	mlx_funcs->mlx_add_pre_render_hook
		= (t_mlx_add_pre_render_hook)
		mlx_get_proc_addr(mlx, "mlx_add_pre_render_hook");
}

void	load_mlx_bindings(mlx_context mlx, t_mlx_funcs *mlx_funcs)
{
	mlx_funcs->mlx_get_vk_device
		= (t_mlx_get_vk_device)mlx_get_proc_addr(mlx, "mlx_get_vk_device");
	mlx_funcs->mlx_get_vk_swapchain_image_count
		= (t_mlx_get_vk_swapchain_image_count)
		mlx_get_proc_addr(mlx, "mlx_get_vk_swapchain_image_count");
	mlx_funcs->mlx_get_vk_swapchain_extent
		= (t_mlx_get_vk_swapchain_extent)
		mlx_get_proc_addr(mlx, "mlx_get_vk_swapchain_extent");
	mlx_funcs->mlx_get_vk_swapchain_format
		= (t_mlx_get_vk_swapchain_format)
		mlx_get_proc_addr(mlx, "mlx_get_vk_swapchain_format");
	mlx_funcs->mlx_get_vk_swapchain_image
		= (t_mlx_get_vk_swapchain_image)
		mlx_get_proc_addr(mlx, "mlx_get_vk_swapchain_image");
	mlx_funcs->mlx_get_vk_swapchain_image_view
		= (t_mlx_get_vk_swapchain_image_view)
		mlx_get_proc_addr(mlx, "mlx_get_vk_swapchain_image_view");
	mlx_funcs->mlx_get_current_vk_swapchain_image_idx
		= (t_mlx_get_curr_vk_sc_image_index)
		mlx_get_proc_addr(mlx, "mlx_get_current_vk_swapchain_image_index");
	mlx_funcs->mlx_get_vk_fn
		= (t_mlx_get_vk_fn)mlx_get_proc_addr(mlx, "mlx_get_vk_fn");
	load_utils_mlx_bindings(mlx, mlx_funcs);
}

void	load_vulkan_bindings(mlx_context mlx, t_mlx_funcs *mlx_funcs,
	t_vulkan_funcs *vulkan_funcs)
{
	vulkan_funcs->vk_cmd_begin_render_pass = (VK_CMD_BEGIN_RENDER_PASS)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkCmdBeginRenderPass");
	vulkan_funcs->vk_cmd_end_render_pass = (VK_CMD_END_RENDER_PASS)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkCmdEndRenderPass");
	vulkan_funcs->vk_create_descriptor_pool = (VK_CREATE_DESCRIPTOR_POOL)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkCreateDescriptorPool");
	vulkan_funcs->vk_create_frame_buffer = (VK_CREATE_FRAME_BUFFER)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkCreateFramebuffer");
	vulkan_funcs->vk_create_render_pass = (VK_CREATE_RENDER_PASS)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkCreateRenderPass");
	vulkan_funcs->vk_destroy_frame_buffer = (VK_DESTROY_FRAME_BUFFER)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkDestroyFramebuffer");
	vulkan_funcs->vk_destroy_render_pass = (VK_DESTROY_RENDER_PASS)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkDestroyRenderPass");
	vulkan_funcs->vk_device_wait_idle = (VK_DEVICE_WAIT_IDLE)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkDeviceWaitIdle");
	vulkan_funcs->vk_get_instance_proc_addr = (VK_GET_INSTANCE_PROC_ADDR)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkGetInstanceProcAddr");
	vulkan_funcs->vk_get_phsic_dvice_surface_cap_khr
		= (VK_GET_PHYSIC_DVICE_SURFACE_CAP_KHR)mlx_funcs->mlx_get_vk_fn
		(mlx, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	vulkan_funcs->vk_destroy_descriptor_pool = (VK_DESTROY_DESCRIPTOR_POOL)
		mlx_funcs->mlx_get_vk_fn(mlx, "vkDestroyDescriptorPool");
}

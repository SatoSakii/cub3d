/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:11:08 by albernar          #+#    #+#             */
/*   Updated: 2025/03/14 18:30:46 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H
# include <mlx.h>
# include <mlx_extended.h>
# include <vulkan/vulkan_core.h>
# include <stdlib.h>
# include <string.h>
# define VK_CREATE_DESCRIPTOR_POOL	PFN_vkCreateDescriptorPool
# define VK_CREATE_RENDER_PASS	PFN_vkCreateRenderPass
# define VK_CREATE_FRAME_BUFFER	PFN_vkCreateFramebuffer
# define VK_DESTROY_FRAME_BUFFER PFN_vkDestroyFramebuffer
# define VK_DEVICE_WAIT_IDLE	PFN_vkDeviceWaitIdle
# define VK_DESTROY_RENDER_PASS	PFN_vkDestroyRenderPass
# define VK_CMD_BEGIN_RENDER_PASS	PFN_vkCmdBeginRenderPass
# define VK_CMD_END_RENDER_PASS	PFN_vkCmdEndRenderPass
# define VK_GET_INSTANCE_PROC_ADDR	PFN_vkGetInstanceProcAddr
# define VK_GET_PHYSIC_DVICE_SURFACE_CAP_KHR	\
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
# define VK_DESTROY_DESCRIPTOR_POOL	PFN_vkDestroyDescriptorPool
# define T_VK_VOID_FUNC	PFN_vkVoidFunction

typedef VkDevice			(*t_mlx_get_vk_device)(mlx_context);
typedef VkFormat			(*t_mlx_get_vk_swapchain_format)(mlx_context,
	mlx_window);
typedef unsigned int		(*t_mlx_get_vk_swapchain_image_count)(mlx_context,
	mlx_window);
typedef VkExtent2D			(*t_mlx_get_vk_swapchain_extent)(mlx_context,
	mlx_window);
typedef VkImageView			(*t_mlx_get_vk_swapchain_image_view)(mlx_context,
	mlx_window, unsigned int);
typedef unsigned int		(*t_mlx_get_curr_vk_sc_image_index)\
	(mlx_context, mlx_window);
typedef mlx_function		(*t_mlx_get_vk_fn)(mlx_context, const char*);
typedef void				(*t_mlx_set_sdl_input_hook)(mlx_context,
	void(*f)(void*));
typedef VkPhysicalDevice	(*t_mlx_get_vk_physical_device)(mlx_context);
typedef VkQueue				(*t_mlx_get_vk_graphics_queue)(mlx_context);
typedef unsigned int		(*t_mlx_get_vk_graphics_queue_family)(mlx_context);
typedef VkInstance			(*t_mlx_get_vk_instance)(mlx_context);
typedef VkSurfaceKHR		(*t_mlx_get_vk_surface)(mlx_context, mlx_window);
typedef void				(*t_mlx_add_pre_render_hook)(mlx_context,
	mlx_window, void(*f)(VkCommandBuffer, void*), void* param);
typedef void*				(*t_mlx_get_window_handle)(mlx_context,
	mlx_window);
typedef VkImage				(*t_mlx_get_vk_swapchain_image)(mlx_context,
	mlx_window, unsigned int);
typedef void				(*t_sdl_hook)(void *);

typedef struct s_mlx_funcs
{
	t_mlx_get_vk_device					mlx_get_vk_device;
	t_mlx_get_vk_swapchain_format		mlx_get_vk_swapchain_format;
	t_mlx_get_vk_swapchain_image_count	mlx_get_vk_swapchain_image_count;
	t_mlx_get_vk_swapchain_image_view	mlx_get_vk_swapchain_image_view;
	t_mlx_get_vk_swapchain_image		mlx_get_vk_swapchain_image;
	t_mlx_get_vk_swapchain_extent		mlx_get_vk_swapchain_extent;
	t_mlx_get_curr_vk_sc_image_index	mlx_get_current_vk_swapchain_image_idx;
	t_mlx_get_vk_fn						mlx_get_vk_fn;
	t_mlx_set_sdl_input_hook			mlx_set_sdl_input_hook;
	t_mlx_get_vk_physical_device		mlx_get_vk_physical_device;
	t_mlx_get_vk_graphics_queue			mlx_get_vk_graphics_queue;
	t_mlx_get_vk_graphics_queue_family	mlx_get_vk_graphics_queue_family;
	t_mlx_get_vk_instance				mlx_get_vk_instance;
	t_mlx_get_vk_surface				mlx_get_vk_surface;
	t_mlx_add_pre_render_hook			mlx_add_pre_render_hook;
	t_mlx_get_window_handle				mlx_get_window_handle;
}	t_mlx_funcs;

typedef struct s_vulkan_funcs
{
	VK_CREATE_DESCRIPTOR_POOL			vk_create_descriptor_pool;
	VK_CREATE_RENDER_PASS				vk_create_render_pass;
	VK_CREATE_FRAME_BUFFER				vk_create_frame_buffer;
	VK_DESTROY_FRAME_BUFFER				vk_destroy_frame_buffer;
	VK_DEVICE_WAIT_IDLE					vk_device_wait_idle;
	VK_DESTROY_RENDER_PASS				vk_destroy_render_pass;
	VK_CMD_BEGIN_RENDER_PASS			vk_cmd_begin_render_pass;
	VK_CMD_END_RENDER_PASS				vk_cmd_end_render_pass;
	VK_GET_INSTANCE_PROC_ADDR			vk_get_instance_proc_addr;
	VK_GET_PHYSIC_DVICE_SURFACE_CAP_KHR	vk_get_phsic_dvice_surface_cap_khr;
	VK_DESTROY_DESCRIPTOR_POOL			vk_destroy_descriptor_pool;
}	t_vulkan_funcs;

t_vulkan_funcs		*get_vulkan_funcs(void);
t_mlx_funcs			*get_mlx_funcs(void);
void				load_vulkan_bindings(mlx_context mlx,
						t_mlx_funcs *mlx_funcs, t_vulkan_funcs *vulkan_funcs);
void				load_mlx_bindings(mlx_context mlx, t_mlx_funcs *mlx_funcs);
PFN_vkVoidFunction	imgui_load_vulkan(const char *name, void *data);

#endif
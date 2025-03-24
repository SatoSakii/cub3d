/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:47:06 by albernar          #+#    #+#             */
/*   Updated: 2025/03/14 18:11:30 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "vulkan_manager.h"

static void	init_pool_sizes(VkDescriptorPoolSize pool_sizes[11])
{
	pool_sizes[0] = (VkDescriptorPoolSize){.type = VK_DESCRIPTOR_TYPE_SAMPLER,
		.descriptorCount = 1000};
	pool_sizes[1] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		.descriptorCount = 1000};
	pool_sizes[2] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, .descriptorCount = 1000};
	pool_sizes[3] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, .descriptorCount = 1000};
	pool_sizes[4] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, .descriptorCount = 1000};
	pool_sizes[5] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, .descriptorCount = 1000};
	pool_sizes[6] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, .descriptorCount = 1000};
	pool_sizes[7] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, .descriptorCount = 1000};
	pool_sizes[8] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
		.descriptorCount = 1000};
	pool_sizes[9] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
		.descriptorCount = 1000};
	pool_sizes[10] = (VkDescriptorPoolSize)
	{.type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, .descriptorCount = 1000};
}

VkDescriptorPool	vulkan_create_descriptor_pool(mlx_context mlx)
{
	const t_vulkan_funcs		*vulkan_funcs = get_vulkan_funcs();
	const VkDescriptorPoolSize	pool_sizes[11];
	VkDescriptorPoolCreateInfo	pool_info;
	VkDescriptorPool			pool;

	init_pool_sizes((VkDescriptorPoolSize *)pool_sizes);
	pool_info = (VkDescriptorPoolCreateInfo){0};
	pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	pool_info.maxSets
		= 1000 * ((int)(sizeof(pool_sizes) / sizeof(*(pool_sizes))));
	pool_info.poolSizeCount
		= ((int)(sizeof(pool_sizes) / sizeof(*(pool_sizes))));
	pool_info.pPoolSizes = pool_sizes;
	vulkan_funcs->vk_create_descriptor_pool(
		get_mlx_funcs()->mlx_get_vk_device(mlx), &pool_info, NULL, &pool);
	return (pool);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_party.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:20:06 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 19:42:45 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THIRD_PARTY_H
# define THIRD_PARTY_H

typedef struct s_render_data
{
	VkInstance			instance;
	VkPhysicalDevice	physical_device;
	VkDevice			device;
	VkDescriptorPool	pool;
	VkRenderPass		renderpass;
	VkFramebuffer		*framebuffers;
	VkExtent2D			swapchain_extent;
}	t_render_data;

#endif
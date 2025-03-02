/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:50:57 by stetrel           #+#    #+#             */
/*   Updated: 2025/03/02 20:05:29 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

unsigned int rgb_to_hex(int r, int g, int b);
void	print_fps(void);
void render(void *param);
void key_hook_down(int key, void *param);
void key_hook_release(int key, void *param);

#endif

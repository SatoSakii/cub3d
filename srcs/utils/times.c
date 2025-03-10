/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 03:36:16 by albernar          #+#    #+#             */
/*   Updated: 2025/03/07 04:31:28 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_delta_time(void)
{
	static struct timeval	last_ts = {0};
	struct timeval			current_ts;
	double					delta_time;

	gettimeofday(&current_ts, NULL);
	delta_time = (current_ts.tv_sec - last_ts.tv_sec)
		+ (current_ts.tv_usec - last_ts.tv_usec) / 1000000.0;
	last_ts = current_ts;
	return (delta_time);
}

void	print_fps(void)
{
	static struct timeval	last_ts = {0};
	static int				frames = 0;
	struct timeval			current_ts;
	double					seconds;

	gettimeofday(&current_ts, NULL);
	frames++;
	seconds = (current_ts.tv_sec - last_ts.tv_sec)
		+ (current_ts.tv_usec - last_ts.tv_usec) / 1000000.0;
	ft_printf("FPS: %d\n", (int)(frames / seconds));
	frames = 0;
	last_ts = current_ts;
}

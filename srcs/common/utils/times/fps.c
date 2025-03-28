/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:07:47 by albernar          #+#    #+#             */
/*   Updated: 2025/03/28 19:25:43 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

void	print_fps(void)
{
	static struct timeval	last_ts = {0};
	static int				frames = 0;
	struct timeval			current_ts;
	double					seconds;

	if (last_ts.tv_sec == 0 && last_ts.tv_usec == 0)
		gettimeofday(&last_ts, NULL);
	gettimeofday(&current_ts, NULL);
	frames++;
	seconds = (current_ts.tv_sec - last_ts.tv_sec)
		+ (current_ts.tv_usec - last_ts.tv_usec) / 1000000.0;
	if (seconds >= TIME_BEETWEEN_FPS_PRINT)
	{
		printf("FPS: %.2f\n", frames / seconds);
		frames = 0;
		last_ts = current_ts;
	}
}

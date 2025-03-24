/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:07:28 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 18:11:24 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_need.h"

double	get_delta_time(void)
{
	static struct timeval	last_ts = {0};
	struct timeval			current_ts;
	double					delta_time;

	if (last_ts.tv_sec == 0 && last_ts.tv_usec == 0)
		gettimeofday(&last_ts, NULL);
	gettimeofday(&current_ts, NULL);
	delta_time = (current_ts.tv_sec - last_ts.tv_sec)
		+ (current_ts.tv_usec - last_ts.tv_usec) / 1000000.0;
	last_ts = current_ts;
	return (delta_time);
}

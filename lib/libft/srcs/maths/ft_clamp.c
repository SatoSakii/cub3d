/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:36:19 by albernar          #+#    #+#             */
/*   Updated: 2025/03/19 16:45:35 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_maths.h"

int	ft_iclamp(int value, int min, int max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

float	ft_fclamp(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

double	ft_dclamp(double value, double min, double max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dvec3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:34:12 by albernar          #+#    #+#             */
/*   Updated: 2025/03/23 23:24:49 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_maths.h"
#include "math.h"

t_dvec3d	ft_dvec3d_add(t_dvec3d a, t_dvec3d b)
{
	return ((t_dvec3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_dvec3d	ft_dvec3d_sub(t_dvec3d a, t_dvec3d b)
{
	return ((t_dvec3d){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_dvec3d	ft_dvec3d_scale(t_dvec3d a, double scale)
{
	return ((t_dvec3d){a.x * scale, a.y * scale, a.z * scale});
}

double	ft_dvec3d_norm(t_dvec3d a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_dvec3d	ft_dvec3d_normalize(t_dvec3d a)
{
	double	magnitude;

	magnitude = ft_dvec3d_norm(a);
	if (magnitude == 0)
		return (a);
	return ((t_dvec3d){a.x / magnitude, a.y / magnitude, a.z / magnitude});
}

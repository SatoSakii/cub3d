/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_maths.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:36:22 by albernar          #+#    #+#             */
/*   Updated: 2025/03/23 22:00:57 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATHS_H
# define LIBFT_MATHS_H

typedef struct s_dvec3d
{
	double	x;
	double	y;
	double	z;
}	t_dvec3d;

typedef struct s_fvec3d
{
	float	x;
	float	y;
	float	z;
}	t_fvec3d;

typedef struct s_ivec3d
{
	int	x;
	int	y;
	int	z;
}	t_ivec3d;

typedef struct s_dvec2d
{
	double	x;
	double	y;
}	t_dvec2d;

typedef struct s_fvec2d
{
	float	x;
	float	y;
}	t_fvec2d;

typedef struct s_ivec2d
{
	int	x;
	int	y;
}	t_ivec2d;

// Double Vector 3D
t_dvec3d	ft_dvec3d_add(t_dvec3d a, t_dvec3d b);
t_dvec3d	ft_dvec3d_sub(t_dvec3d a, t_dvec3d b);
t_dvec3d	ft_dvec3d_scale(t_dvec3d a, double scale);
double		ft_dvec3d_norm(t_dvec3d a);
t_dvec3d	ft_dvec3d_normalize(t_dvec3d a);

int			ft_sqrt(int nb);
int			ft_iclamp(int value, int min, int max);
float		ft_fclamp(float value, float min, float max);
double		ft_dclamp(double value, double min, double max);
int			ft_abs(int n);
long long	ft_llabs(long long n);

#endif
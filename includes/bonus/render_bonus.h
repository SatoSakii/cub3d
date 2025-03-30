/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:09:18 by albernar          #+#    #+#             */
/*   Updated: 2025/03/30 15:26:27 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

typedef struct s_textures
{
	int			width;
	int			height;
	char		*path;
	void		*addr;
	mlx_image	img;
	mlx_color	*pixels;
}	t_textures;

typedef struct s_colors
{
	int				r;
	int				g;
	int				b;
	unsigned int	color;
}	t_colors;

typedef struct s_render
{
	int			x;
	int			line_height;
	double		wall_x;
	t_walldir	side;
}	t_render;

typedef struct s_ray
{
	double		camera_x;
	double		perp_wall_dist;
	t_dvec2d	ray_dir;
	t_dvec2d	delta_dist;
	t_dvec2d	side_dist;
	t_ivec2d	step;
	t_ivec2d	map;
	bool		hit;
}	t_ray;

typedef struct s_mlx
{
	mlx_context				ctx;
	mlx_window_create_info	info;
	mlx_window				win;
	t_render_data			render;
}	t_mlx;

#endif
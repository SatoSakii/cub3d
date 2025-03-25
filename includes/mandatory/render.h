/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:11:42 by albernar          #+#    #+#             */
/*   Updated: 2025/03/24 19:38:13 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

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
	bool		inside_wall;
}	t_render;

typedef struct s_ray
{
	double		camera_x;
	double		perpwalldist;
	t_dvec2d	raydir;
	t_dvec2d	deltadist;
	t_dvec2d	sidedist;
	t_ivec2d	step;
	t_ivec2d	map;
	bool		hit;
	bool		inside_wall;
}	t_ray;

typedef struct s_mlx
{
	mlx_context				ctx;
	mlx_window_create_info	info;
	mlx_window				win;
}	t_mlx;

#endif
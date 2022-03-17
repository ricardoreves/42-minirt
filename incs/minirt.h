/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:42:00 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/17 20:32:50 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "../libgnl/incs/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_color
{
	size_t	r;
	size_t	g;
	size_t	b;
}	t_color;

typedef struct s_ambient
{
	char	id;
	float	lighting;
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	char		id;
	t_vector	coords;
	float		brightness;
	t_color		color;
}	t_light;

typedef struct s_camera
{
	char		id;
	t_vector	coords;
	t_vector	orient;
	size_t		fov;
}	t_camera;

typedef struct s_plane
{
	char		id;
	t_vector	coords;
	t_vector	orient;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	char		id;
	t_vector	coords;
	t_vector	orient;
	float		diameter;
	float		height;
	t_color		color;
}	t_cylinder;

typedef struct s_sphere
{
	char		id;
	t_vector	coords;
	float		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_rt
{
	t_ambient	ambient;
	t_light		light;
	t_camera	camera;
}	t_rt;

#endif
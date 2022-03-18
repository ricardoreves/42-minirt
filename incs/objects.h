/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:08:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/18 23:16:53 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# define ERR_TOO_FEW_OBJ_ARG "too few object arguments"
# define ERR_TOO_FEW_COORS_VAL "too few coordinates values"
# define ERR_TOO_FEW_ORIENT_VAL "too few orientation values"
# define ERR_TOO_FEW_COLOR_VAL "too few color values"
# define ERR_NOT_A_ULONG "value is not a unsigned long"
# define ERR_NOT_A_FLOAT "value is not a float"

typedef enum e_object_id
{
	id_ambient,
	id_light,
	id_camera,
	id_plane,
	id_cylinder,
	id_sphere
}	t_object_id;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_ambient
{
	t_object_id	id;
	float	lighting;
	int		color;
}	t_ambient;

typedef struct s_light
{
	t_object_id	id;
	t_vector	coords;
	float		brightness;
	int			color;
}	t_light;

typedef struct s_camera
{
	t_object_id	id;
	t_vector	coords;
	t_vector	orient;
	size_t		fov;
}	t_camera;

typedef struct s_plane
{
	t_object_id	id;
	t_vector	coords;
	t_vector	orient;
	int			color;
}	t_plane;

typedef struct s_cylinder
{
	t_object_id	id;
	t_vector	coords;
	t_vector	orient;
	float		diameter;
	float		height;
	int			color;
}	t_cylinder;

typedef struct s_sphere
{
	t_object_id	id;
	t_vector	coords;
	float		diameter;
	int			color;
}	t_sphere;

typedef union u_object
{
	t_ambient	ambient;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object_union;

typedef struct s_object
{
	t_object_id		id;
	t_object_union	object;
	struct s_object	*next;
}	t_object;

#endif

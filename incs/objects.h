/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:08:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/14 17:55:20 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# define ERR_TOO_MANY_LIGTHS "too many light params"
# define ERR_TOO_MANY_CAMERAS "too many camera params"
# define ERR_TOO_MANY_AMBIENTS "too many ambient params"
# define ERR_MISSING_LIGHT_PARAMS "missing light params"
# define ERR_MISSING_CAMERA_PARAMS "missing camera params"
# define ERR_MISSING_AMBIENT_PARAMS "missing ambient params"
# define ERR_INVALID_EXTRA_PARAMS "invalid extra params"
# define ERR_INVALID_NB_PARAMS "invalid number of params"
# define ERR_INVALID_NB_COORDS "invalid number of coordinates values"
# define ERR_INVALID_NB_ORIENT "invalid number of orientation values"
# define ERR_INVALID_NB_COLORS "invalid number of color values"
# define ERR_NOT_A_ULONG "value is not a unsigned long"
# define ERR_NOT_A_FLOAT "value is not a float"

typedef enum e_object_id
{
	id_unset,
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

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t1;
	float	t2;
}	t_quadratic;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef	struct s_ray
{
	t_vector	or;
	t_vector	dir;
}	t_ray;

typedef	struct s_hit
{
	t_vector	nHit;
	t_vector	pHit;
	float		t;
}	t_hit;

typedef struct s_ambient
{
	t_object_id	id;
	float		lighting;
	t_color		color;

}	t_ambient;

typedef struct s_light
{
	t_object_id	id;
	t_vector	coords;
	float		brightness;
	t_color		color;
}	t_light;

typedef struct s_camera
{
	t_object_id	id;
	t_vector	coords;
	t_vector	orient;
	size_t		fov;
	float		scale;
}	t_camera;

typedef struct s_plane
{
	t_object_id	id;
	t_vector	coords;
	t_vector	orient;
	t_color		color;

}	t_plane;

typedef struct s_cylinder
{
	t_object_id	id;
	t_vector	coords;
	t_vector	orient;
	float		diameter;
	float		height;
	float		r2;
	t_vector	p1;
	t_vector	p2;
	t_vector	delta_p;
	t_color		color;

}	t_cylinder;

typedef struct s_sphere
{
	t_object_id	id;
	t_vector	coords;
	float		diameter;
	float		r2;
	t_color		color;

}	t_sphere;

typedef union u_object
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object_union;

typedef struct s_object
{
	t_object_id		id;
	t_object_union	object;
	float			speckv;
	float			specn;
	float			mirror;
	struct s_object	*next;
}	t_object;

#endif

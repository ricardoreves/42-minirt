/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:08:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/20 04:05:31 by bgoncalv         ###   ########.fr       */
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
	id_cone,
	id_sphere,
	id_triangle
}	t_obj_id;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}	t_vect;

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
	t_vect	or;
	t_vect	dir;
}	t_ray;

typedef	struct s_hit
{
	t_vect		nHit;
	t_vect		pHit;
	float		t;
	t_color		color;
}	t_hit;


typedef struct s_colors
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	reflect;
	t_color	refract;
	int		is_shadow;
}	t_colors;

typedef struct s_ambient
{
	t_obj_id	id;
	float		lighting;
	t_color		color;

}	t_ambient;

typedef struct s_light
{
	t_obj_id		id;
	t_vect			coords;
	float			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	t_obj_id	id;
	t_vect		coords;
	t_vect		orient;
	size_t		fov;
	float		scale;
}	t_camera;

typedef struct s_plane
{
	t_obj_id	id;
	t_vect		coords;
	t_vect		orient;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_obj_id	id;
	t_vect		coords;
	t_vect		orient;
	float		diameter;
	float		height;
	float		r2;
	t_vect		p1;
	t_vect		p2;
	t_vect		delta_p;
	t_color		color;
}	t_cylinder;

typedef struct s_sphere
{
	t_obj_id	id;
	t_vect		coords;
	float		diameter;
	float		r2;
	t_color		color;
}	t_sphere;

typedef struct s_triangle
{
	t_obj_id	id;
	t_vect		c[3];
	t_vect		edge[3];
	t_vect		n;
	t_color		color;
	float		area2;
}	t_triangle;

typedef struct s_cone
{
	t_obj_id	id;
	t_vect		coords;
	t_vect		orient;
	float		h;
	float		angle;
	float		cos2;
	t_vect		c2;
	t_color		color;
}	t_cone;

typedef union u_object
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_cone		cone;
	t_triangle	triangle;
}	t_obj_union;

typedef struct s_obj
{
	t_obj_id		id;
	t_obj_union		object;
	float			speckv;
	float			specn;
	float			mirror;
	float			refract;
	t_vect			e1;
	t_vect			e2;
	t_vect			coords;
	t_color			color;
	t_color			second_color;
	float			pattern_len;
	int				pattern_num;
	struct s_obj	*next;
}	t_obj;

typedef struct s_rays
{
	t_ray		prime_ray;
	t_ray		shadowray;
	t_hit		hit;
	t_hit		shadow_hit;
	t_obj		*closest_obj;
}	t_rays;

#endif

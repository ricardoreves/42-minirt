/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:08:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/18 13:38:33 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_ambient
{
	float	lighting;
	int		color;
}	t_ambient;

typedef struct s_light
{
	t_vector	coords;
	float		brightness;
	int			color;
}	t_light;

typedef struct s_camera
{
	t_vector	coords;
	t_vector	orient;
	size_t		fov;
}	t_camera;

typedef struct s_plane
{
	t_vector	coords;
	t_vector	orient;
	int			color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	coords;
	t_vector	orient;
	float		diameter;
	float		height;
	int			color;
}	t_cylinder;

typedef struct s_sphere
{
	t_vector	coords;
	float		diameter;
	int			color;
}	t_sphere;

typedef enum e_object_id
{
	AMBIANT_ID,
	LIGHT_ID,
	CAMERA_ID,
	PLANE_ID,
	CYLINDER_ID,
	SPHERE_ID
}	t_object_id;

union u_object
{
	t_ambient	*ambiant;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
};

typedef struct s_object
{
	t_object_id		id;
	union u_object	*object;
	struct s_object	*next;
}	t_object;

#endif

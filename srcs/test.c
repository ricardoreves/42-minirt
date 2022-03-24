/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 02:31:21 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/24 22:31:45 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void init_cam(t_rt *rt)
{
	t_camera	*cam = &rt->camera;

	cam->id = id_camera;
	cam->coords.x = -50;
	cam->coords.y = 0;
	cam->coords.z = 20;
	cam->orient.x = 0;
	cam->orient.y = 0;
	cam->orient.z = 1;
	cam->fov = 70;
}

static void add_sphere(t_object_union *obj, float x, float y, float z, float dim, int color)
{
	obj->sphere.coords.x = x;
	obj->sphere.coords.y = y;
	obj->sphere.coords.z = z;
	obj->sphere.diameter = dim;
	obj->sphere.color = color;
}

static void add_plane(t_object_union *obj, float x, float y, float z,
							float x2, float y2, float z2, int color)
{
	obj->plane.coords.x = x;
	obj->plane.coords.y = y;
	obj->plane.coords.z = z;
	obj->plane.orient.x = x2;
	obj->plane.orient.y = y2;
	obj->plane.orient.z = z2;
	obj->plane.color = color;
}

void	init_test(t_rt *rt)
{	t_object	*new_obj;

	init_cam(rt);
	new_obj = create_object(rt);
	new_obj->id = id_sphere;
	add_sphere(&new_obj->object, -50, 10, 500, 2 , 0xFF5600);
	new_obj = create_object(rt);
	new_obj->id = id_plane;
	add_plane(&new_obj->object, 0, 0, 0 , 0, 0, 1.0, 0xFF0000);
}
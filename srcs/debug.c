/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 00:34:39 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/20 01:30:16 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void rt_dump(t_rt *rt)
{
	t_object *tmp;

	if (rt->camera.id)
	{
		printf("object: camera\n");
		printf("id    : %d\n", rt->camera.id);
		printf("cx    : %f\n", rt->camera.coords.x);
		printf("cy    : %f\n", rt->camera.coords.y);
		printf("cz    : %f\n", rt->camera.coords.z);
		printf("ox    : %f\n", rt->camera.orient.x);
		printf("oy    : %f\n", rt->camera.orient.y);
		printf("oz    : %f\n", rt->camera.orient.z);
		printf("fov   : %ld\n", rt->camera.fov);
	}
	tmp = rt->objs;
	while (tmp)
	{
		if (tmp->id == id_ambient)
		{
			printf("object: ambient\n");
			printf("id    : %d\n", tmp->id);
			printf("color : %d\n", tmp->object.ambient.color);
			printf("ligth : %f\n", tmp->object.ambient.lighting);
		}
		if (tmp->id == id_light)
		{
			printf("object: light\n");
			printf("id    : %d\n", tmp->id);
			printf("cx    : %f\n", tmp->object.light.coords.x);
			printf("cy    : %f\n", tmp->object.light.coords.y);
			printf("cz    : %f\n", tmp->object.light.coords.z);
			printf("color : %d\n", tmp->object.light.color);
			printf("bright: %f\n", tmp->object.light.brightness);
		}
		if (tmp->id == id_plane)
		{
			printf("object: plane\n");
			printf("id    : %d\n", tmp->id);
			printf("cx    : %f\n", tmp->object.plane.coords.x);
			printf("cy    : %f\n", tmp->object.plane.coords.y);
			printf("cz    : %f\n", tmp->object.plane.coords.z);
			printf("ox    : %f\n", tmp->object.plane.orient.x);
			printf("oy    : %f\n", tmp->object.plane.orient.y);
			printf("oz    : %f\n", tmp->object.plane.orient.z);
			printf("color : %d\n", tmp->object.plane.color);
		}
		if (tmp->id == id_cylinder)
		{
			printf("object: cylinder\n");
			printf("id    : %d\n", tmp->id);
			printf("cx    : %f\n", tmp->object.cylinder.coords.x);
			printf("cy    : %f\n", tmp->object.cylinder.coords.y);
			printf("cz    : %f\n", tmp->object.cylinder.coords.z);
			printf("ox    : %f\n", tmp->object.cylinder.orient.x);
			printf("oy    : %f\n", tmp->object.cylinder.orient.y);
			printf("oz    : %f\n", tmp->object.cylinder.orient.z);
			printf("diamet: %f\n", tmp->object.cylinder.diameter);
			printf("height: %f\n", tmp->object.cylinder.height);
			printf("color : %d\n", tmp->object.cylinder.color);
		}
		if (tmp->id == id_sphere)
		{
			printf("object: sphere\n");
			printf("id    : %d\n", tmp->id);
			printf("cx    : %f\n", tmp->object.sphere.coords.x);
			printf("cy    : %f\n", tmp->object.sphere.coords.y);
			printf("cz    : %f\n", tmp->object.sphere.coords.z);
			printf("diamet: %f\n", tmp->object.sphere.diameter);
			printf("color : %d\n", tmp->object.sphere.color);
		}
		tmp = tmp->next;
	}
}
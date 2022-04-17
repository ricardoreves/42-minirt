/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:38:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/17 18:23:13 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	object_norm(t_rt *rt)
{
	t_cylinder	*cy;
	t_obj		*objs;

	objs = rt->objs;
	while (objs)
	{
		if (objs->id == id_sphere)
			objs->object.sphere.r2 = pow(objs->object.sphere.diameter / 2, 2);
		if (objs->id == id_cylinder)
		{
			cy = &objs->object.cylinder;
			normalize(&cy->orient);
			cy->r2 = cy->diameter * cy->diameter * 0.25;
			cy->delta_p = vect_mul(cy->orient, cy->height);
			cy->p1 = vect_mul(cy->orient, -0.5 * cy->height);
			cy->p1 = vect_add(cy->p1, cy->coords);
			cy->p2 = vect_mul(cy->orient, 0.5 * cy->height);
			cy->p2 = vect_add(cy->p2, cy->coords);
		}
		objs->refract = 0;
		if (objs->mirror < 0)
			objs->refract = -objs->mirror;
		set_patternref(rt, objs);

		// to take off later;
		if (objs->id == id_sphere)
			objs->color = objs->object.sphere.color;
		if (objs->id == id_plane)
			objs->color = objs->object.plane.color;
		if (objs->id == id_cylinder)
			objs->color = objs->object.cylinder.color;
		objs->color = color_obj(objs);
		// end takeoff

		objs = objs->next;
	}
}

void	push_object(t_object *obj, t_object **objs)
{
	t_object	*tmp;

	if (!(*objs))
		*objs = obj;
	else
	{
		tmp = *objs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
}

t_object	*create_object(t_rt *rt)
{
	t_object	*obj;

	obj = ft_calloc(sizeof(t_object), 1);
	obj->speckv = SPECULAR_KV;
	obj->specn = SPECULAR_N;
	obj->mirror = MIRROR;
	push_object(obj, &rt->objs);
	rt->num_objs++;
	return (obj);
}

void	free_objects(t_object **objs)
{
	t_object	*tmp;
	t_object	*obj;

	obj = *objs;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	*objs = 0;
}

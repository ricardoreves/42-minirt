/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:38:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/20 04:09:43 by bgoncalv         ###   ########.fr       */
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
		if (objs->id == id_cone)
		{
			normalize(&objs->object.cone.orient);
			objs->object.cone.cos2 = pow(cos(objs->object.cone.angle), 2);
			objs->object.cone.c2 = vect_mul(objs->object.cone.orient, objs->object.cone.h);
			objs->object.cone.c2 = vect_add(objs->object.cone.c2, objs->object.cone.coords);
		}
		if (objs->id == id_triangle)
		{
			objs->object.triangle.edge[0] = vect_sub(objs->object.triangle.c[0], objs->object.triangle.c[1]);
			objs->object.triangle.edge[1] = vect_sub(objs->object.triangle.c[1], objs->object.triangle.c[2]);
			objs->object.triangle.edge[2] = vect_sub(objs->object.triangle.c[2], objs->object.triangle.c[0]);
			objs->object.triangle.n = cross_prod(objs->object.triangle.edge[0], objs->object.triangle.edge[1]);
			objs->object.triangle.area2 = vectlen(objs->object.triangle.n);
			normalize(&objs->object.triangle.n);
			
		}
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
		set_patternref(rt, objs);
		objs = objs->next;
	}
}

void	push_object(t_obj *obj, t_obj **objs)
{
	t_obj	*tmp;

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

t_obj	*create_object(t_rt *rt, t_obj_id id)
{
	t_obj	*obj;

	obj = ft_calloc(sizeof(t_obj), 1);
	obj->id = id;
	obj->speckv = SPECULAR_KV;
	obj->specn = SPECULAR_N;
	obj->mirror = MIRROR;
	obj->refract = REFRACT;
	obj->pattern_len = PATTERN_LEN;
	obj->pattern_num = PATTERN_NUM;
	push_object(obj, &rt->objs);
	rt->num_objs++;
	return (obj);
}

void	free_objects(t_obj **objs)
{
	t_obj	*tmp;
	t_obj	*obj;

	obj = *objs;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	*objs = 0;
}

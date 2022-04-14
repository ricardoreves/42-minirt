/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:38:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/15 01:11:48 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	object_norm(t_obj *objs)
{
	t_cylinder	*cy;

	while (objs)
	{
		if (objs->id == id_sphere)
			objs->object.sphere.r2 = pow(objs->object.sphere.diameter / 2, 2);
		if (objs->id == id_cylinder)
		{
			cy = &objs->object.cylinder;
			normalize(&cy->orient);
			cy->r2 = cy->diameter * cy->diameter * 0.25;
			vect_mul(&cy->delta_p, &cy->orient, cy->height);
			vect_mul(&cy->p1, &cy->orient, -0.5 * cy->height);
			vect_add(&cy->p1, &cy->p1, &cy->coords);
			vect_mul(&cy->p2, &cy->orient, 0.5 * cy->height);
			vect_add(&cy->p2, &cy->p2, &cy->coords);
		}
		objs = objs->next;
	}
}

void push_object(t_object *obj, t_object **objs)
{
	t_object *tmp;

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

t_object *create_object(t_rt *rt)
{
	t_object *obj;

	obj = ft_calloc(sizeof(t_object), 1);
	obj->speckv = SPECULAR_KV;
	obj->specn = SPECULAR_N;
	obj->mirror = MIRROR;
	push_object(obj, &rt->objs);
	rt->num_objs++;
	return (obj);
}

void free_objects(t_object **objs)
{
	t_object *tmp;
	t_object *obj;

	obj = *objs;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	*objs = 0;
}

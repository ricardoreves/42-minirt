/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:38:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/22 17:18:37 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	*get_coords(t_obj *o)
{
	if (!o)
		return (NULL);
	if (o->id == id_plane)
		return (&o->object.plane.coords);
	if (o->id == id_sphere)
		return (&o->object.sphere.coords);
	if (o->id == id_cone)
		return (&o->object.cone.coords);
	if (o->id == id_cylinder)
		return (&o->object.cylinder.coords);
	return (NULL);	
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
	obj->has_bump = FALSE;
	obj->texture.img = NULL;
	obj->has_texture = FALSE;
	obj->bump.img = NULL;
	push_object(obj, &rt->objs);
	rt->num_objs++;
	return (obj);
}

void	free_objects(t_rt *rt, t_obj **objs)
{
	t_obj	*tmp;
	t_obj	*obj;

	obj = *objs;
	(void)rt;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	*objs = 0;
}

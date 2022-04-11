/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:38:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/07 22:47:17 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

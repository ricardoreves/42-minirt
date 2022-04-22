/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:38:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/22 02:33:32 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		if (obj->has_texture)
		{
			mlx_destroy_image(rt->mlx, obj->texture.img);
			ft_memdel((void **) &obj->texture.path);
		}
		if (obj->has_bump)
		{
			mlx_destroy_image(rt->mlx, obj->bump.img);
			ft_memdel((void **) &obj->bump.path);
		}
		free(tmp);
	}
	*objs = 0;
}

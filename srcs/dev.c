/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:48:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/20 03:06:41 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int argc, char **argv)
{
	t_rt *rt;
	t_object *tmp;

	rt = ft_calloc(sizeof(t_rt), 1);
	if (argc != 2)
		ft_putendl_fd("Error: please provide a scene file.", 2);
	else if (open_file(rt, argv[1]))
	{
		printf("sadfadsfsadfasfdadsfadsf");
		if (rt->camera.id)
		{
			printf("obj: camera\n");
			printf("id: %d\n", rt->camera.id);
			printf("cx: %f\n", rt->camera.coords.x);
			printf("cy: %f\n", rt->camera.coords.y);
			printf("cz: %f\n", rt->camera.coords.z);
			printf("ox: %f\n", rt->camera.orient.x);
			printf("oy: %f\n", rt->camera.orient.y);
			printf("oz: %f\n", rt->camera.orient.z);
			printf("fov: %ld\n", rt->camera.fov);
		}
		tmp = rt->objs;
		while (tmp)
		{
			if (tmp->id == id_ambient)
			{
				printf("obj: ambient\n");
				printf("id: %d\n", tmp->id);
				printf("co: %d\n", tmp->object.ambient.color);
				printf("li: %f\n", tmp->object.ambient.lighting);
			}
			tmp = tmp->next;
		}
	}
	rt_free(rt);
	return (0);
}
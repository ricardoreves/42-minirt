/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 16:54:20 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/17 17:07:54 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_patternref(t_rt *rt, t_obj *obj)
{
	t_vect	n;

	n = vector(0, 1, 0);
	if (obj->id == id_plane)
		n = obj->object.plane.orient;
	if (obj->id == id_cylinder)
		n = obj->object.cylinder.orient;
	obj->e1 = cross_prod(n, rt->camera.orient);
	obj->e2 = cross_prod(n, obj->e1);
	normalize(&obj->e1);
	normalize(&obj->e2);
	obj->second_color = newcolor(0, 0, 0);
}

t_color	checkboard_color(t_obj *obj, t_vector pHit)
{
	t_vect	pi;
	float	mu[2];
	pi = vect_sub(pHit, obj->coords);
	mu[0] = dot_prod(pi, obj->e1);
	mu[1] = dot_prod(pi, obj->e2);
	if (((int) (2 * mu[0]) + (int) mu[1]) & 1)
		return (obj->color);
	return (obj->second_color);
}

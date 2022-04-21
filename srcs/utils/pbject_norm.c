/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbject_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:36:43 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/21 02:56:03 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	triangle_norm(t_rt *rt, t_triangle *t)
{
	t_vect	v;
	t_vect	tmp;

	t->edge[0] = vect_sub(t->c[0], t->c[1]);
	t->edge[1] = vect_sub(t->c[1], t->c[2]);
	t->edge[2] = vect_sub(t->c[2], t->c[0]);
	t->n = cross_prod(t->edge[0], t->edge[1]);
	t->area2 = vectlen(t->n);
	normalize(&t->n);
	v = vect_sub(rt->camera.orient, t->c[0]);
	if (dot_prod(v, t->n) > 0)
	{
		tmp = t->c[1];
		t->c[1] = t->c[2];
		t->c[2] = tmp;
		triangle_norm(rt, t);
	}
}

void	cone_norm(t_cone *c)
{
	normalize(&c->orient);
	c->cos2 = pow(cos(c->angle), 2);
	c->c1 = vect_mul(c->orient, c->h);
	c->c1 = vect_add(c->c1, c->coords);
	c->c2 = vect_mul(c->orient, -c->h2);
	c->c2 = vect_add(c->c2, c->coords);
	c->r1 = tan(c->angle) * c->h;
	c->r2 = tan(c->angle) * c->h2;
}

void	cylinder_norm(t_cylinder *cy)
{
	normalize(&cy->orient);
	cy->r2 = cy->diameter * cy->diameter * 0.25;
	cy->delta_p = vect_mul(cy->orient, cy->height);
	cy->p1 = vect_mul(cy->orient, -0.5 * cy->height);
	cy->p1 = vect_add(cy->p1, cy->coords);
	cy->p2 = vect_mul(cy->orient, 0.5 * cy->height);
	cy->p2 = vect_add(cy->p2, cy->coords);
}

void	object_norm(t_rt *rt)
{
	t_obj		*objs;

	objs = rt->objs;
	while (objs)
	{
		if (objs->id == id_sphere)
			objs->object.sphere.r2 = pow(objs->object.sphere.diameter / 2, 2);
		if (objs->id == id_cone)
			cone_norm(&objs->object.cone);
		if (objs->id == id_triangle)
			triangle_norm(rt, &objs->object.triangle);
		if (objs->id == id_cylinder)
			cylinder_norm(&objs->object.cylinder);
		set_patternref(rt, objs);
		objs = objs->next;
	}
}


// void	object_norm(t_rt *rt)
// {
// 	t_cylinder	*cy;
// 	t_obj		*objs;

// 	objs = rt->objs;
// 	while (objs)
// 	{
// 		if (objs->id == id_sphere)
// 			objs->object.sphere.r2 = pow(objs->object.sphere.diameter / 2, 2);
// 		if (objs->id == id_cone)
// 		{
// 			normalize(&objs->object.cone.orient);
// 			objs->object.cone.cos2 = pow(cos(objs->object.cone.angle), 2);
// 			objs->object.cone.c2 = vect_mul(objs->object.cone.orient, objs->object.cone.h);
// 			objs->object.cone.c2 = vect_add(objs->object.cone.c2, objs->object.cone.coords);
// 		}
// 		if (objs->id == id_cylinder)
// 		{
// 			cy = &objs->object.cylinder;
// 			normalize(&cy->orient);
// 			cy->r2 = cy->diameter * cy->diameter * 0.25;
// 			cy->delta_p = vect_mul(cy->orient, cy->height);
// 			cy->p1 = vect_mul(cy->orient, -0.5 * cy->height);
// 			cy->p1 = vect_add(cy->p1, cy->coords);
// 			cy->p2 = vect_mul(cy->orient, 0.5 * cy->height);
// 			cy->p2 = vect_add(cy->p2, cy->coords);
// 		}
// 		set_patternref(rt, objs);
// 		objs = objs->next;
// 	}
// }
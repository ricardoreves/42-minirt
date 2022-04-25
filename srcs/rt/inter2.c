/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:10:41 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/25 17:52:02 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	cone_inter(t_ray *r, t_cone *co, t_hit *hit)
{
	t_plane	pl;
	t_hit	tmp_hit;

	hit->t = INFINITY;
	pl.coords = co->c1;
	pl.orient = co->orient;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.phit, co->c1)
		<= co->r1 && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	pl.coords = co->c2;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.phit, co->c2)
		<= co->r2 && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (conic_inter(r, co, &tmp_hit) && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (dot_prod(hit->nhit, r->dir) > 0)
		hit->nhit = vect_inv(hit->nhit);
	return (hit->t < INFINITY && hit->t > EPSILON);
}

t_bool	triangle_inter(t_ray *r, t_triangle *t, t_hit *hit)
{
	float	dot_prod_ndir;
	float	d;
	t_vect	m;
	int		i;

	dot_prod_ndir = dot_prod(t->n, r->dir);
	if (fabs(dot_prod_ndir) < EPSILON)
		return (FALSE);
	d = -dot_prod(t->n, t->c[0]);
	hit->t = -(dot_prod(r->or, t->n) + d) / dot_prod_ndir;
	if (hit->t < EPSILON)
		return (FALSE);
	ray_mul(&hit->phit, r, hit->t);
	i = -1;
	while (++i < 3)
	{
		m = cross_prod(t->edge[i], vect_sub(t->c[i], hit->phit));
		if (dot_prod(t->n, m) < 0)
			return (FALSE);
	}
	hit->nhit = t->n;
	if (dot_prod(hit->nhit, r->dir) > 0)
		hit->nhit = vect_inv(hit->nhit);
	return (TRUE);
}

int	intersect(t_ray *ray, t_obj *obj, t_hit *hit)
{
	if (obj->id == id_sphere)
		return (sphere_inter(ray, &obj->object.sphere, hit));
	if (obj->id == id_plane)
		return (plane_inter(ray, &obj->object.plane, hit));
	if (obj->id == id_cylinder)
		return (cylinder_inter(ray, &obj->object.cylinder, hit));
	if (obj->id == id_cone)
		return (cone_inter(ray, &obj->object.cone, hit));
	if (obj->id == id_triangle)
		return (triangle_inter(ray, &obj->object.triangle, hit));
	return (FALSE);
}

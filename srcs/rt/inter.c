/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:10:41 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/14 03:03:45 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	sphere_inter(t_ray *ray, t_sphere *sp, t_vect *pHit, t_vect *nHit)
{
	t_vector	l;
	float		tca;
	float		d2;
	float		thc;
	float		t[2];

	vect_sub(&l, &ray->or, &sp->coords);
	tca = dot_prod(&l, &ray->dir);
	if (tca < 0)
		return (FALSE);
	d2 = dot_prod(&l, &l) - tca * tca;
	if (d2 > sp->r2)
		return (FALSE);
	thc = sqrt(sp->r2 - d2);
	t[0] = tca - thc;
	t[1] = tca + thc;
	if (t[0] < 0 && t[1] < 0)
		return (FALSE);
	if (t[0] < 0 || t[1] < t[0])
		t[0] = t[1];
	if (!pHit || !nHit)
		return (TRUE);
	ray_mul(pHit, ray, t[0]);
	vect_sub(nHit, &sp->coords, pHit);
	normalize(nHit);
	return (TRUE);
}

t_bool	plane_inter(t_ray *r, t_plane *pl, t_vect *pHit, t_vect *nHit)
{
	float	denom;
	float	t;
	t_vect	tmp;

	denom = dot_prod(&pl->orient, &r->dir);
	if (denom == 0)
		return (FALSE);
	vect_sub(&tmp, &r->or, &pl->coords);
	t = dot_prod(&tmp, &pl->orient) / denom;
	if (t < EPSILON)
		return (FALSE);
	if (!pHit || !nHit)
		return (TRUE);
	ray_mul(pHit, r, t);
	*nHit = pl->orient;
	if (dot_prod(nHit, &r->dir) > 0)
		vect_inv(nHit);
	return (TRUE);
}

t_bool	infinite_cyl_inter(t_ray *r, t_cylinder *cy, t_vect *pHit, t_vect *nHit)
{
	t_quadratic	q;
	t_vect		u;
	t_vect		v;

	u = cross_prod(&r->dir, &cy->orient);
	vect_sub(&v, &cy->coords, &r->or);
	v = cross_prod(&v, &cy->orient);
	q.a = dot_prod(&u, &u);
	q.b = 2 * dot_prod(&u, &v);
	q.c = dot_prod(&v, &v) - cy->r2;
	if (!solve_quadratic(&q) || (q.t2 <= 0 && q.t1 <= 0))
		return (FALSE);
	if (q.t1 <= 0)
		q.t1 = q.t2;
	ray_mul(pHit, r, q.t1);
	vect_sub(&v, &cy->coords, pHit);
	*nHit = cross_prod(&v, &cy->orient);
	normalize(nHit);
	return (TRUE);
}

t_bool	cylinder_inter(t_ray *r, t_cylinder *cy, t_vect *pHit, t_vect *nHit)
{
	t_vect	cp;

	if (1)
		return (infinite_cyl_inter(r, cy, pHit, nHit));
	if (!infinite_cyl_inter(r, cy, pHit, nHit))
		return (FALSE);
	vect_sub(&cp, &cy->coords, pHit);
	if (dot_prod(&cp, &cp) > pow(cy->height * 0.5, 2) + cy->diameter * cy->diameter * 0.25)
		return (FALSE);
	return (TRUE);
}

int	intersect(t_ray *ray, t_object *obj, t_vect *pHit, t_vect *nHit)
{
	if (obj->id == id_sphere)
		return (sphere_inter(ray, &obj->object.sphere, pHit, nHit));
	if (obj->id == id_plane)
		return (plane_inter(ray, &obj->object.plane, pHit, nHit));
	if (obj->id == id_cylinder)
		return (cylinder_inter(ray, &obj->object.cylinder, pHit, nHit));
	return (FALSE);
}


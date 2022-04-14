/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:10:41 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/15 00:28:05 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	sphere_inter(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_vector	l;
	float		tca;
	float		d2;
	float		thc;
	float		t2;

	vect_sub(&l, &ray->or, &sp->coords);
	tca = dot_prod(&l, &ray->dir);
	if (tca < 0)
		return (FALSE);
	d2 = dot_prod(&l, &l) - tca * tca;
	if (d2 > sp->r2)
		return (FALSE);
	thc = sqrt(sp->r2 - d2);
	hit->t = tca - thc;
	t2 = tca + thc;
	if (hit->t < 0 && t2 < 0)
		return (FALSE);
	if (hit->t < 0 || t2 < hit->t)
		hit->t = t2;
	ray_mul(&hit->pHit, ray, hit->t);
	vect_sub(&hit->nHit, &sp->coords, &hit->pHit);
	normalize(&hit->nHit);
	return (TRUE);
}

t_bool	plane_inter(t_ray *r, t_plane *pl, t_hit *hit)
{
	float	denom;
	t_vect	tmp;

	denom = dot_prod(&pl->orient, &r->dir);
	if (denom == 0)
		return (FALSE);
	vect_sub(&tmp, &r->or, &pl->coords);
	hit->t = dot_prod(&tmp, &pl->orient) / denom;
	if (hit->t < EPSILON)
		return (FALSE);
	ray_mul(&hit->pHit, r, hit->t);
	hit->nHit = pl->orient;
	if (dot_prod(&hit->nHit, &r->dir) > 0)
		vect_inv(&hit->nHit);
	return (TRUE);
}

t_bool	infinite_cyl_inter(t_ray *r, t_cylinder *cy, t_hit *hit)
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
	if (q.t1 <= 0 || (q.t2 > 0 && (q.t2 < q.t1)))
		q.t1 = q.t2;
	hit->t = q.t1;
	ray_mul(&hit->pHit, r, q.t1);
	vect_sub(&v, &cy->coords, &hit->pHit);
	hit->nHit = cross_prod(&v, &cy->orient);
	hit->nHit = cross_prod(&hit->nHit, &cy->orient);
	normalize(&hit->nHit); // maybe need to inverse?
	if (dot_prod(&hit->nHit, &r->dir))
		vect_inv(&hit->nHit);
	return (TRUE);
}

t_bool	cylinder_inter(t_ray *r, t_cylinder *cy, t_hit *hit)
{
	t_plane	pl;
	t_hit	tmp_hit;

	if (infinite_cyl_inter(r, cy, hit) == FALSE)
		return (FALSE);
	if (pow(distance(&cy->coords, &hit->pHit), 2) > pow(cy->height * 0.5, 2) + cy->r2)
		return (FALSE);
	pl.coords = cy->p1;
	pl.orient = cy->orient;
	if (plane_inter(r, &pl, &tmp_hit) && distance(&tmp_hit.pHit, &cy->p1) < cy->diameter * 0.5)
		*hit = tmp_hit;
	pl.coords = cy->p2;
	if (plane_inter(r, &pl, &tmp_hit) && distance(&tmp_hit.pHit, &cy->p2) < cy->diameter * 0.5)
		*hit = tmp_hit;
	return (TRUE);
}

int	intersect(t_ray *ray, t_object *obj, t_hit *hit)
{
	if (obj->id == id_sphere)
		return (sphere_inter(ray, &obj->object.sphere, hit));
	if (obj->id == id_plane)
		return (plane_inter(ray, &obj->object.plane, hit));
	if (obj->id == id_cylinder)
		return (cylinder_inter(ray, &obj->object.cylinder, hit));
	return (FALSE);
}


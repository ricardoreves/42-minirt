/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:10:41 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/20 00:19:44 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	sphere_inter(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_vect	l;
	float		tca;
	float		d2;
	float		thc;
	float		t2;

	l = vect_sub(ray->or, sp->coords);
	tca = dot_prod(l, ray->dir);
	if (tca < 0)
		return (FALSE);
	d2 = dot_prod(l, l) - tca * tca;
	if (d2 > sp->r2)
		return (FALSE);
	thc = sqrt(sp->r2 - d2);
	hit->t = tca - thc;
	t2 = tca + thc;
	if (hit->t < EPSILON && t2 < EPSILON)
		return (FALSE);
	if (hit->t < EPSILON || t2 < hit->t)
		hit->t = t2;
	ray_mul(&hit->pHit, ray, hit->t);
	hit->nHit = vect_sub(sp->coords, hit->pHit);
	normalize(&hit->nHit);
	return (TRUE);
}

t_bool	plane_inter(t_ray *r, t_plane *pl, t_hit *hit)
{
	float	denom;
	t_vect	tmp;

	denom = dot_prod(pl->orient, r->dir);
	if (denom == 0)
		return (FALSE);
	tmp = vect_sub(r->or, pl->coords);
	hit->t = dot_prod(tmp, pl->orient) / denom;
	if (hit->t < EPSILON)
		return (FALSE);
	ray_mul(&hit->pHit, r, hit->t);
	hit->nHit = pl->orient;
	if (dot_prod(hit->nHit, r->dir) > 0)
		hit->nHit = vect_inv(hit->nHit);
	return (TRUE);
}

t_bool	infinite_cyl_inter(t_ray *r, t_cylinder *cy, t_hit *hit)
{
	t_quadratic	q;
	t_vect		u;
	t_vect		v;

	u = cross_prod(r->dir, cy->orient);
	v = vect_sub(cy->coords, r->or);
	v = cross_prod(v, cy->orient);
	q.a = dot_prod(u, u);
	q.b = 2 * dot_prod(u, v);
	q.c = dot_prod(v, v) - cy->r2;
	if (!solve_quadratic(&q) || (q.t2 <= EPSILON && q.t1 <= EPSILON))
		return (FALSE);
	if (q.t1 <= EPSILON || (q.t2 > EPSILON && (q.t2 < q.t1)))
		q.t1 = q.t2;
	hit->t = q.t1;
	ray_mul(&hit->pHit, r, q.t1);
	v = vect_sub(cy->coords, hit->pHit);
	hit->nHit = cross_prod(v, cy->orient);
	hit->nHit = cross_prod(hit->nHit, cy->orient);
	normalize(&hit->nHit);
	if (dot_prod(hit->nHit, r->dir))
		hit->nHit = vect_inv(hit->nHit);
	return (TRUE);
}

t_bool	cylinder_inter(t_ray *r, t_cylinder *cy, t_hit *hit)
{
	t_plane	pl;
	t_hit	tmp_hit;

	hit->t = INFINITY;
	pl.coords = cy->p1;
	pl.orient = cy->orient;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.pHit, cy->p1)
		<= cy->diameter * 0.5 && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	pl.coords = cy->p2;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.pHit, cy->p2) <= cy->diameter * 0.5
		&& hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (infinite_cyl_inter(r, cy, &tmp_hit)
		&& pow(distance(cy->coords, tmp_hit.pHit), 2)
		<= pow(cy->height * 0.5, 2) + cy->r2
		&& hit->t > tmp_hit.t)
		*hit = tmp_hit;
	return (hit->t < INFINITY && hit->t > EPSILON);
}

t_bool	conic_inter(t_ray *r, t_cone *co, t_hit *hit)
{
	t_quadratic	q;
	float		prod_dv;
	float		prod_cov;
	t_vect		v_co;
	t_vect		cp;

	v_co = vect_sub(co->coords, r->or);
	prod_dv = dot_prod(r->dir, co->orient);
	prod_cov = dot_prod(v_co, co->orient);
	q.a = prod_dv * prod_dv - co->cos2;
	q.b = 2 * (prod_dv * prod_cov - dot_prod(r->dir, v_co) * co->cos2);
	q.c = prod_cov * prod_cov - dot_prod(v_co, v_co) * co->cos2;
	if (!solve_quadratic(&q) || (q.t2 <= EPSILON && q.t1 <= EPSILON))
		return (FALSE);
	if (q.t1 <= EPSILON || (q.t2 > EPSILON && (q.t2 < q.t1)))
		q.t1 = q.t2;
	hit->t = q.t1;
	ray_mul(&hit->pHit, r, hit->t);
	cp = vect_sub(co->coords, hit->pHit);
	if (dot_prod(co->orient, cp) > co->h || dot_prod(cp, co->orient) < 0)
		return (FALSE);
	hit->nHit = cross_prod(cross_prod(cp, co->orient), cp);
	normalize(&hit->nHit);
	return (TRUE);
}

t_bool	cone_inter(t_ray *r, t_cone *co, t_hit *hit)
{
	t_plane	pl;
	t_hit	tmp_hit;

	hit->t = INFINITY;
	pl.coords = co->c2;
	pl.orient = co->orient;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.pHit, co->c2)
		<= tan(co->angle) * co->h && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (conic_inter(r, co, &tmp_hit) && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	return (hit->t < INFINITY && hit->t > EPSILON);
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
	return (FALSE);
}

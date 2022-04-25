/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:10:41 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/25 17:51:49 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	sphere_inter(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_vect	l;
	float	tca;
	float	d2;
	float	thc;
	float	t2;

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
	ray_mul(&hit->phit, ray, hit->t);
	hit->nhit = vect_sub(sp->coords, hit->phit);
	normalize(&hit->nhit);
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
	ray_mul(&hit->phit, r, hit->t);
	hit->nhit = pl->orient;
	if (dot_prod(hit->nhit, r->dir) > 0)
		hit->nhit = vect_inv(hit->nhit);
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
	ray_mul(&hit->phit, r, q.t1);
	v = vect_sub(cy->coords, hit->phit);
	hit->nhit = cross_prod(v, cy->orient);
	hit->nhit = cross_prod(hit->nhit, cy->orient);
	normalize(&hit->nhit);
	if (dot_prod(hit->nhit, r->dir))
		hit->nhit = vect_inv(hit->nhit);
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
		&& distance(tmp_hit.phit, cy->p1)
		<= cy->diameter * 0.5 && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	pl.coords = cy->p2;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.phit, cy->p2) <= cy->diameter * 0.5
		&& hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (infinite_cyl_inter(r, cy, &tmp_hit)
		&& pow(distance(cy->coords, tmp_hit.phit), 2)
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
	ray_mul(&hit->phit, r, hit->t);
	cp = vect_sub(co->coords, hit->phit);
	if (dot_prod(co->orient, cp) > co->h || dot_prod(co->orient, cp) < -co->h2)
		return (FALSE);
	hit->nhit = cross_prod(cross_prod(cp, co->orient), cp);
	normalize(&hit->nhit);
	return (TRUE);
}

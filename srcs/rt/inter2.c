/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:10:41 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/21 03:07:22 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (dot_prod(co->orient, cp) > co->h || dot_prod(co->orient, cp) < -co->h2)
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
	pl.coords = co->c1;
	pl.orient = co->orient;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.pHit, co->c1)
		<= co->r1 && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	pl.coords = co->c2;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.pHit, co->c2)
		<= co->r2 && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (conic_inter(r, co, &tmp_hit) && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (dot_prod(hit->nHit, r->dir) > 0)
		hit->nHit = vect_inv(hit->nHit);
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
	ray_mul(&hit->pHit, r, hit->t);
	i = -1;
	while (++i < 3)
	{
		m = cross_prod(t->edge[i], vect_sub(t->c[i], hit->pHit));
		if (dot_prod(t->n, m) < 0)
			return (FALSE);
	}
	hit->nHit = t->n;
	if (dot_prod(hit->nHit, r->dir) > 0)
		hit->nHit = vect_inv(hit->nHit);
	return (TRUE);
}

// t_bool	triangle_inter(t_ray *r, t_triangle *t, t_hit *hit)
// {
// 	float	dot_prod_ndir;
// 	float	d;
// 	t_vect	m;
// 	t_vect	cp;

// 	dot_prod_ndir = dot_prod(t->n, r->dir);
// 	if (fabs(dot_prod_ndir) < EPSILON)
// 		return (FALSE);
// 	d = -dot_prod(t->n, t->c[0]);
// 	hit->t = -(dot_prod(r->or, t->n) + d) / dot_prod_ndir;
// 	if (hit->t < EPSILON)
// 		return (FALSE);
// 	ray_mul(&hit->pHit, r, hit->t);

// 	cp = vect_sub(t->c[0], hit->pHit);
// 	m = cross_prod(t->edge[0], cp);
// 	if (dot_prod(t->n, m) < 0)
// 		return (FALSE);

// 	cp = vect_sub(t->c[1], hit->pHit);
// 	m = cross_prod(t->edge[1], cp);
// 	if (dot_prod(t->n, m) < 0)
// 		return (FALSE);

// 	cp = vect_sub(t->c[2], hit->pHit);
// 	m = cross_prod(t->edge[2], cp);
// 	if (dot_prod(t->n, m) < 0)
// 		return (FALSE);
// 	hit->nHit = t->n;
// 	if (dot_prod(hit->nHit, r->dir) > 0)
// 		hit->nHit = vect_inv(hit->nHit);
// 	return (TRUE);
// }

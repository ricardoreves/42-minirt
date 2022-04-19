/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:10:41 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/20 00:24:22 by bgoncalv         ###   ########.fr       */
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
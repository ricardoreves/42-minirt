/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:10:41 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/06 04:01:19 by bgoncalv         ###   ########.fr       */
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

	vectres(&l, &ray->or, &sp->coords);
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
	ray_mul(pHit, ray, t[0]);
	vectres(nHit, &sp->coords, pHit);
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
	vectres(&tmp, &r->or, &pl->coords);
	t = dot_prod(&tmp, &pl->orient) / denom;
	if (t < 0)
		return (FALSE);
	ray_mul(pHit, r, t);
	*nHit = pl->orient;
	return (TRUE);
}

t_bool	cylinder_inter(t_ray *r, t_cylinder *cy, t_vect *pHit, t_vect *nHit)
{
	(void) r;
	(void) pHit;
	(void) nHit;
	(void) cy;

	return (FALSE);
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


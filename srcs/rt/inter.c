/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:10:41 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/04 21:18:40 by bgoncalv         ###   ########.fr       */
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
	// printf("test\n");
	if (t[0] < 0 && t[1] < 0)
		return (FALSE);
	if (t[0] < 0 || (t[1] > 0 && t[1] < t[0]))
		t[0] = t[1];
	ray_mul(pHit, ray, t[0]);
	vectres(nHit, &sp->coords, pHit);
	normalize(nHit);
	return (TRUE);
}

void	swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_bool	quadratic_solve(float a, float b, float c, float *t0, float *t1)
{
	float	discr;
	float	q;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (FALSE);
	if (discr == 0)
	{
		*t0 = - 0.5 * b / a;
		*t0 = *t1;
		return (TRUE);
	}
	discr = sqrt(discr);
	if ( b > 0)
		q = -0.5 * (b + discr);
	else
		q = -0.5 * (b - discr);
	*t0 = q / a;
	*t1 = c / q;
	if (*t0 > *t1)
		swap(t0, t1);
	return (TRUE);
}

// t_bool	sphere_inter(t_ray *ray, t_sphere *sp, t_vect *pHit, t_vect *nHit)
// {
// 	t_vector	l;
// 	float		a;
// 	float		b;
// 	float		c;
// 	float		t[2];

// 	vectres(&l, &sp->coords, &ray->or);
// 	a = dot_prod(&ray->dir, &ray->dir);
// 	b = 2 * dot_prod(&ray->dir, &l);
// 	c = dot_prod(&l, &l) - sp->r2;
// 	if (!quadratic_solve(a, b, c, &t[0], &t[1]))
// 		return (FALSE);
// 	if (t[0] < 0 && t[1] < 0)
// 		return (FALSE);
// 	if (t[0] < 0 || (t[1] > 0 && t[1] < t[0]))
// 		t[0] = t[1];
// 	ray_mul(pHit, ray, t[0]);
// 	vectres(nHit, &sp->coords, pHit);
// 	normalize(nHit);
// 	return (TRUE);
// }

t_bool	plane_inter(t_ray *r, t_plane *pl, t_vect *pHit, t_vect *nHit)
{
	float	denom;
	float	t;

	denom = dot_prod(normalize(&pl->orient), &r->dir);
	if (denom == 0)
		return (FALSE);
	vectres(pHit, &r->or, &pl->coords);
	t = dot_prod(pHit, &pl->orient) / denom;
	if (t < 0)
		return (FALSE);
	ray_mul(pHit, r, t);
	*nHit = pl->orient;
	normalize(nHit);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray->c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:48:55 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/24 15:57:27 by bgoncalv         ###   ########.fr       */
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
	printf("%f   %f   %f   len : %f\n", ray->dir.x, ray->dir.y, ray->dir.z, vectlen(&ray->dir));
	printf("t:%f tca:%f thc:%f \n", t[0], tca, thc);
	printf("d2:%f   lx:%f ly:%f lz:%f llen:%f  l.l:%f\n", d2, l.x, l.y, l.z, vectlen(&l), dot_prod(&l, &l));
	printf("yeah\n");
	printf("(%f, %f, %f)   diam: %f r: %f \n", sp->coords.x,sp->coords.y,sp->coords.z, sp->diameter, sp->r2);
	return (TRUE);
}

t_bool	plane_inter(t_ray *r, t_plane *pl, t_vect *pHit, t_vect *nHit)
{
	(void) r;
	(void) pHit;
	(void) nHit;
	(void) pl;

	return (FALSE);
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

t_object	*get_closest_obj(t_ray *ray, t_object *obj, t_vect *pHit, t_vect *nHit)
{
	float		min_dist;
	float		dist;
	t_object	*closest_obj;

	closest_obj = NULL;
	min_dist = INFINITY;
	while (obj)
	{
		if (intersect(ray, obj, pHit, nHit))
		{
			dist = distance(&ray->or, pHit);
			if (dist < min_dist)
			{
				closest_obj = obj;
				min_dist = dist;
			}
		}
		obj = obj->next;
	}
	return (closest_obj);
}

int	color_obj(t_obj *obj)
{
	if (obj && obj->id == id_sphere)
		return (obj->object.sphere.color);
	if (obj && obj->id == id_plane)
		return (obj->object.plane.color);
	if (obj && obj->id == id_cylinder)
		return (obj->object.cylinder.color);
	return (0);
}

int	raytrace(t_ray *ray, t_rt *rt)
{
	int			color;
	t_vect		pHit;
	t_vect		nHit;
	t_object	*closest_obj;

	color = (int) (ray->dir.x + ray->dir.y);
	vect_init(&ray->dir, ray->or.x + ray->dir.x, ray->or.y + ray->dir.y, ray->or.z + 1); // careful need to be transform with matrix to world
	vectres(&ray->dir, &ray->or, &ray->dir);
	normalize(&ray->dir);
	closest_obj = get_closest_obj(ray, rt->objs, &pHit, &nHit);
	if (closest_obj)
		return (color_obj(closest_obj));
	return (0);
}

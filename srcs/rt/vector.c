/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 00:56:26 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/17 01:01:02 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	vector(float x, float y, float z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

float	vectlen(t_vector *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

t_vect	*vect_sub(t_vector *dst, t_vector *a, t_vector *b)
{
	dst->x = b->x - a->x;
	dst->y = b->y - a->y;
	dst->z = b->z - a->z;
	return (dst);
}

t_vect	*vect_add(t_vector *dst, t_vector *a, t_vector *b)
{
	dst->x = b->x + a->x;
	dst->y = b->y + a->y;
	dst->z = b->z + a->z;
	return (dst);
}

t_vect	*vect_mul(t_vect *dst, t_vect *v, float f)
{
	dst->x = v->x * f;
	dst->y = v->y * f;
	dst->z = v->z * f;
	return (dst);
}

t_vector	*ray_mul(t_vect *dst, t_ray *r, float t)
{
	dst->x = r->or.x + t * r->dir.x;
	dst->y = r->or.y + t * r->dir.y;
	dst->z = r->or.z + t * r->dir.z;
	return (dst);
}

t_vector reflect_vect(t_vector v, t_vector n)
{
	t_vect	dst;

	vect_mul(&dst, &n, 2 * dot_prod(&v, &n));
	vect_sub(&dst, &dst, &v);
	return (dst);
}

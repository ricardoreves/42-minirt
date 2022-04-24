/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 00:56:26 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 16:34:36 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	vector(float x, float y, float z)
{
	t_vect	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

float	vectlen(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vect	vect_sub(t_vect a, t_vect b)
{
	t_vect	dst;

	dst.x = b.x - a.x;
	dst.y = b.y - a.y;
	dst.z = b.z - a.z;
	return (dst);
}

t_vect	vect_add(t_vect a, t_vect b)
{
	t_vect	dst;

	dst.x = b.x + a.x;
	dst.y = b.y + a.y;
	dst.z = b.z + a.z;
	return (dst);
}

t_vect	vect_mul(t_vect v, float f)
{
	t_vect	dst;

	dst.x = v.x * f;
	dst.y = v.y * f;
	dst.z = v.z * f;
	return (dst);
}

float	dot_prod(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vect	cross_prod(t_vect u, t_vect v)
{
	t_vect	dst;

	dst.x = u.y * v.z - u.z * v.y;
	dst.y = u.z * v.x - u.x * v.z;
	dst.z = u.x * v.y - u.y * v.x;
	return (dst);
}

float	distance(t_vect a, t_vect b)
{
	float	x;
	float	y;
	float	z;

	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
	x = pow(x, 2);
	y = pow(y, 2);
	z = pow(z, 2);
	return (sqrt(x + y + z));
}

t_vect	vect_inv(t_vect v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

t_vect	*normalize(t_vect *v)
{
	float	norm;

	norm = 1 / vectlen(*v);
	v->x *= norm;
	v->y *= norm;
	v->z *= norm;
	return (v);
}

t_vect	reflect_vect(t_vect v, t_vect n)
{
	t_vect	dst;

	dst = vect_mul(n, 2 * dot_prod(v, n));
	dst = vect_sub(dst, v);
	return (dst);
}

t_vect	refract_vect(t_vect v, t_vect n, float eta)
{
	float	c1;
	float	c2;
	t_vect	dst;

	c1 = dot_prod(v, n);
	c2 = sqrt(1 - eta * eta * (1 - c1 * c1));
	dst = vect_mul(n, eta * c1 - c2);
	dst = vect_add(dst, vect_mul(v, eta));
	normalize(&dst);
	return (dst);
}

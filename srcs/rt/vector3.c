/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 00:56:26 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/17 05:09:08 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*ray_mul(t_vect *dst, t_ray *r, float t)
{
	dst->x = r->or.x + t * r->dir.x;
	dst->y = r->or.y + t * r->dir.y;
	dst->z = r->or.z + t * r->dir.z;
	return (dst);
}

t_vector	reflect_vect(t_vector v, t_vector n)
{
	t_vect	dst;

	dst = vect_mul(n, 2 * dot_prod(v, n));
	dst = vect_sub(dst, v);
	return (dst);
}

t_vector	refract_vect(t_vector v, t_vector n, float eta) // eta = n1/n2
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

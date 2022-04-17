/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 00:56:26 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/17 01:42:37 by bgoncalv         ###   ########.fr       */
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

	vect_mul(&dst, &n, 2 * dot_prod(&v, &n));
	vect_sub(&dst, &dst, &v);
	return (dst);
}

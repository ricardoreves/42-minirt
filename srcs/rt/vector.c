/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 00:56:26 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/19 02:08:24 by bgoncalv         ###   ########.fr       */
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

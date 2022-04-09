/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:54:52 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/06 01:30:02 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot_prod(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

float	distance(t_vect *a, t_vect *b)
{
	float	x;
	float	y;
	float	z;

	x = a->x - b->x;
	y = a->y - b->y;
	z = a->z - b->z;
	x = pow(x, 2);
	y = pow(y, 2);
	z = pow(z, 2);
	return (sqrt(x + y + z));
}

t_vector	*vect_inv(t_vect *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
	return (v);
}

t_vector	*normalize(t_vector *v)
{
	float	norm;

	norm = 1 / vectlen(v);
	v->x *= norm;
	v->y *= norm;
	v->z *= norm;
	return (v);
}

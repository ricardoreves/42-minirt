/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 00:56:26 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/02 21:57:12 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vect_init(t_vector *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void	vect_cpy(t_vector *dst, t_vector *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

float	vectlen(t_vector *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

void	vectres(t_vector *dst, t_vector *a, t_vector *b)
{
	dst->x = b->x - a->x;
	dst->y = b->y - a->y;
	dst->z = b->z - a->z;
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



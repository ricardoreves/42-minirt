/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 00:56:26 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/23 00:50:05 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vect_init(t_vector *v, float x, float y, float z)
{
	v->x = x;
	v->x = y;
	v->x = z;
}

void	vectcpy(t_vector *dst, t_vector *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
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

	norm = pow(v->x, 2.0) + pow(v->y, 2.0) + pow(v->z, 2.0);
	norm = pow(norm, 0.5);
	v->x /= norm;
	v->y /= norm;
	v->z /= norm;
	return (v);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:46:54 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 15:31:03 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	process_bump_normal(t_obj *obj, t_vect n, float bu, float bv)
{
	t_vect	v;
	t_vect	pu;
	t_vect	pv;

	v = n;
	pu = cross_prod(n, obj->ey);
	pv = cross_prod(n, pu);
	v = vect_add(v, vect_mul(pu, bv));
	v = vect_add(v, vect_mul(pv, bu));
	normalize(&v);
	return (v);
}

void	bump_normal(t_obj *obj, t_img *img, t_hit *hit)
{
	char		*dst;
	int			x[2];
	int			y[2];
	int			c[2];
	float		uv[2];

	uv_sphere_map(obj, hit->pHit, uv);
	x[0] = (((int) ((1 - uv[0]) * img->width)) + img->width / 2) % img->width;
	y[0] = (int) ((1 - uv[1]) * img->height);
	x[1] = (x[0] + 1) % img->width;  // maybe -1
	y[1] = (y[0] + 1) % img->height; // same
	dst = img->addr
		+ (y[0] * img->line_length + x[0] * (img->bits_per_pixel / 8));
	c[0] = *((unsigned int *)dst) & 0xff;
	dst = img->addr
		+ (y[0] * img->line_length + x[1] * (img->bits_per_pixel / 8));
	c[1] = *((unsigned int *)dst) & 0xff;
	uv[0] = -((float) (c[0] - c[1])) / 10;
	dst = img->addr
		+ (y[1] * img->line_length + x[0] * (img->bits_per_pixel / 8));
	c[1] = *((unsigned int *)dst) & 0xff;
	uv[1] = -((float) (c[0] - c[1])) / 10;
	hit->nHit = process_bump_normal(obj, hit->nHit, uv[0], uv[1]);
}

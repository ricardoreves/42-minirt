/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 16:54:20 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/17 17:07:54 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_patternref(t_rt *rt, t_obj *obj)
{
	obj->ey = vector(0, 1, 0);
	if (obj->id == id_plane)
		obj->ey = obj->object.plane.orient;
	if (obj->id == id_cylinder)
	{
		obj->ey = obj->object.cylinder.orient;
		obj->h = obj->object.cylinder.height;
	}
	if (obj->id == id_cone)
	{
		obj->ey = obj->object.cone.orient;
		obj->h = obj->object.cone.h + obj->object.cone.h2;
	}
	obj->ex = cross_prod(obj->ey, rt->camera.orient);
	obj->ez = cross_prod(obj->ex, obj->ey);
	normalize(&obj->ex);
	normalize(&obj->ey);
	normalize(&obj->ez);
}

void	uv_sphere_map(t_obj *obj, t_vect p, float *uv)
{
	t_vect		v;
	float		x;
	float		y;
	float		z;

	v = vect_sub(obj->coords, p);
	normalize(&v);
	x = dot_prod(obj->ex, v);
	y = dot_prod(obj->ey, v);
	z = dot_prod(obj->ez, v);
	uv[0] = atan2(x, z) / (2 * M_PI) + 0.5;
	uv[1] = y * 0.5 + 0.5;
}

void	uv_plane_map(t_obj *obj, t_vect p, float *uv)
{
	t_vect	pi;

	pi = vect_sub(p, obj->coords);
	uv[0] = dot_prod(pi, obj->ex);
	uv[1] = dot_prod(pi, obj->ez);
}

void	uv_cylco_map(t_obj *obj, t_vect p, float *uv)
{
	t_vect		v;
	float		x;
	float		y;
	float		z;

	v = vect_sub(obj->coords, p);
	y = dot_prod(obj->ey, v);
	normalize(&v);
	x = dot_prod(obj->ex, v);
	z = dot_prod(obj->ez, v);
	uv[0] = atan2(x, z) / (2 * M_PI) + 0.5;
	uv[1] = y / obj->h + 0.5;
}

t_color	pattern_color(t_obj *obj, t_vect phit)
{
	float	uv[3];

	//ft_bzero(uv, sizeof(float) * 3);
	if (obj->pattern_num == 0)
		return (obj->color);
	if (obj->id == id_plane)
		uv_plane_map(obj, phit, uv);
	if (obj->id == id_sphere)
		uv_sphere_map(obj, phit, uv);
	if (obj->id == id_cylinder || obj->id == id_cone)
		uv_cylco_map(obj, phit, uv);
	if (obj->pattern_num == 1 && (((int)(uv[0] * obj->pattern_len) + (int)(uv[1]
			* obj->pattern_len)) & 1))
		return (obj->color);
	if (obj->pattern_num == 2 && ((int)(uv[0] * obj->pattern_len)) & 1)
		return (obj->color);
	if (obj->pattern_num == 3 && ((int)(uv[1] * obj->pattern_len)) & 1)
		return (obj->color);
	if (obj->pattern_num < 4)
		return (obj->color2);
	uv[2] = sin(uv[1] * obj->pattern_len);
	if (obj->pattern_num == 4)
		return (mix_color(obj->color, uv[2], obj->color2, 1 - fabs(uv[2])));
	uv[2] = sin(uv[0] * obj->pattern_len) * cos(uv[1] * obj->pattern_len) / 2;
	return (mix_color(obj->color, uv[2], obj->color2, 1 - fabs(uv[2])));
}

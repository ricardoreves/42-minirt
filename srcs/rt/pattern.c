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

// void	set_patternref(t_rt *rt, t_obj *obj)
// {
// 	t_vect	n;

// 	n = vector(0, 1, 0);
// 	if (obj->id == id_plane)
// 		n = obj->object.plane.orient;
// 	if (obj->id == id_cylinder)
// 		n = obj->object.cylinder.orient;
// 	obj->e1 = cross_prod(n, rt->camera.orient);
// 	obj->e2 = cross_prod(n, obj->e1);
// 	normalize(&obj->e1);
// 	normalize(&obj->e2);
// 	obj->second_color = newcolor(0, 0, 0);
// }

// t_color	checkboard_color(t_obj *obj, t_vect pHit)
// {
// 	t_vect	pi;
// 	float	mu[2];
// 	pi = vect_sub(pHit, obj->coords);
// 	mu[0] = dot_prod(pi, obj->e1);
// 	mu[1] = dot_prod(pi, obj->e2);
// 	if (((int) (mu[0] / obj->pattern_len) + (int) (mu[1] / obj->pattern_len)) & 1)
// 		return (obj->color);
// 	return (obj->second_color);
// }

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
	obj->e3 = vector(0, 1, 0);
	if (obj->id == id_plane)
		obj->e3 = obj->object.plane.orient;
	if (obj->id == id_cylinder)
		obj->e3 = obj->object.cylinder.orient;
	obj->e1 = cross_prod(obj->e3, rt->camera.orient);
	if (dot_prod(rt->camera.orient, obj->e3) == 0)
		obj->e2 = vector(1, 0, 0);
	obj->e2 = cross_prod(obj->e3, obj->e1);
	normalize(&obj->e1);
	normalize(&obj->e2);
	normalize(&obj->e3);
}

t_color	plane_map(t_obj *obj, t_vect pHit)
{
	t_vect	pi;
	float	u;
	float	v;
	float	p;
	int		pattern_num = 1;
	int		pattern_len = 10;

	pi = vect_sub(pHit, obj->coords);
	u = dot_prod(pi, obj->e1);
	v = dot_prod(pi, obj->e2);
	if (pattern_num == 1 && (((int) (u / pattern_len) + (int) (v / pattern_len)) & 1))
		return (obj->color);
	else if (pattern_num == 1)
		return (obj->second_color);
	else if (pattern_num == 2)
	{
		p = sin(u * pattern_len) * cos(v * pattern_len) / 2;
		return (mix_color(obj->color, p, obj->second_color, 1 - fabs(p)));
	}
	p = sin(u * pattern_len);
	return (mix_color(obj->color, p, obj->second_color, 1 - fabs(p)));
}

t_color	sphere_map(t_obj *obj, t_vect pHit)
{
	t_vect	pi;
	float	dx;
	float	dy;
	float	p;
	float	u;
	float	v;
	int		pattern_num = 1;
	int		pattern_len = 10;

	pi = vect_sub(pHit, obj->coords);
	// v = dot_prod(pi, obj->e3) / obj->object.sphere.diameter + 0.5;
	dx = dot_prod(pi, obj->e1);
	dy = dot_prod(pi, obj->e2);
	u = atan2(dx, dy) / (2 * M_PI) * pattern_len;
	v = 0;
	if (pattern_num == 1 && (((int) (u * pattern_len) + (int)(v * pattern_len)) & 1))
		return (obj->color);
	else if (pattern_num == 1)
		return (obj->second_color);
	else if (pattern_num == 2)
	{
		p = sin(u * pattern_len) * cos(v * pattern_len) / 2;
		return (mix_color(obj->color, p, obj->second_color, 1 - fabs(p)));
	}
	p = sin(u * pattern_len);
	return (mix_color(obj->color, p, obj->second_color, 1 - fabs(p)));
}

t_color	cylinder_map(t_obj *obj, t_vect pHit)
{
	t_vect	pi;
	float	dx;
	float	dy;
	float	p;
	float	u;
	float	v;
	int		pattern_num = 1;
	int		pattern_len = 10;

	pi = vect_sub(pHit, obj->coords);
	// v = dot_prod(pi, obj->e3) / obj->object.cylinder.height + 0.5;
	dx = dot_prod(pi, obj->e1);
	dy = dot_prod(pi, obj->e2);
	u = (0.5 + atan2(dy, dx) / (2 * M_PI)) * 10;
	v = 0;
	if (pattern_num == 1 && (((int) (u * pattern_len) + (int) (v * pattern_len)) & 1))
		return (obj->color);
	else if (pattern_num == 1)
		return (obj->second_color);
	else if (pattern_num == 2)
	{
		p = sin(u * pattern_len) * cos(v * pattern_len) / 2;
		return (mix_color(obj->color, p, obj->second_color, 1 - fabs(p)));
	}
	p = sin(u * pattern_len);
	return (mix_color(obj->color, p, obj->second_color, 1 - fabs(p)));
}

// void	sphere_map(float *u, float *v, t_obj *obj, t_vect p)
// {
// 	t_vect	pi;
// 	float	dx;
// 	float	dy;
// 	float	dz;

// 	pi = vect_sub(p, obj->coords);
// 	normalize(&pi);
// 	dx = dot_prod(pi, obj->e1);
// 	dy = dot_prod(pi, obj->e2);
// 	dz = dot_prod(pi, obj->e3);
// 	*u = 0.5 + atan2(dx, dz) / (2 * M_PI) * 10;
// 	*v = 0.5 + asin(dy) / M_PI * 10;
// }

t_color	pattern_color(t_obj *obj, t_vect pHit)
{
	if (obj->pattern_num == 0)
		return (obj->color);
	if (obj->id == id_plane)
		return (plane_map(obj, pHit));
	if (obj->id == id_sphere)
		return (sphere_map(obj, pHit));
	if (obj->id == id_cylinder)
		return (cylinder_map(obj, pHit));
	return (obj->color);
}

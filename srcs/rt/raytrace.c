/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:22:36 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 16:27:30 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*get_closest_obj(t_ray *ray, t_obj *obj, t_hit *hit)
{
	float	min_dist;
	t_obj	*closest_obj;
	t_hit	tmp_hit;

	closest_obj = NULL;
	min_dist = INFINITY;
	while (obj)
	{
		if (intersect(ray, obj, &tmp_hit))
		{
			if (tmp_hit.t < min_dist)
			{
				closest_obj = obj;
				min_dist = tmp_hit.t;
				*hit = tmp_hit;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
		hit->color = color_obj(closest_obj, hit);
	return (closest_obj);
}

t_color	light2rgb(t_obj *o, t_colors *colors)
{
	t_color	c;

	c.r = colors->ambient.r + colors->diffuse.r + colors->specular.r;
	c.g = colors->ambient.g + colors->diffuse.g + colors->specular.g;
	c.b = colors->ambient.b + colors->diffuse.b + colors->specular.b;
	if (o && o->mirror > 0)
		c = mix_color(c, 1 - o->mirror, colors->reflect, o->mirror);
	if (o && o->refract > 0)
		c = mix_color(colors->refract, 0.7, c, 0.3);
	if (c.r > 1)
		c.r = 1;
	if (c.g > 1)
		c.g = 1;
	if (c.b > 1)
		c.b = 1;
	return (c);
}

void	handle_lights(t_rt *rt, t_rays *r, t_colors *colors)
{
	t_light	*l;

	colors->ambient = r->hit.color;
	colors->ambient = add_light(colors->ambient, rt->ambient.color,
			rt->ambient.lighting);
	l = rt->light;
	while (l)
	{
		colors->is_shadow = shadow_ray(rt, r, l);
		if (!colors->is_shadow)
			colors->diffuse = mix_color(colors->diffuse, 1,
					diffuse_light(r, l), 1);
		if (!colors->is_shadow)
			colors->specular = mix_color(colors->specular, 1,
					specular_light(r, l), 1);
		l = l->next;
	}
}

t_color	raytrace(t_rt *rt, t_rays *r, int max_reflect)
{
	t_colors	colors;
	t_obj		*o;

	ft_memset(&colors, 0, sizeof(colors));
	r->closest_obj = get_closest_obj(&r->prime_ray, rt->objs, &r->hit);
	o = r->closest_obj;
	if (!r->closest_obj)
		return (newcolor(0, 0, 0));
	if (r->closest_obj->has_bump)
		bump_normal(r->closest_obj, &r->closest_obj->bump, &r->hit);
	handle_lights(rt, r, &colors);
	--max_reflect;
	if (r->closest_obj->mirror > 0 && max_reflect)
		colors.reflect = reflection_ray(rt, r, max_reflect);
	if (r->closest_obj->refract > 0 && max_reflect)
		colors.refract = refraction_ray(rt, r, max_reflect);
	if (max_reflect < 0)
		o = NULL;
	return (light2rgb(o, &colors));
}

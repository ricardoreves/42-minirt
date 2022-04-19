/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:22:36 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/19 03:19:41 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*get_closest_obj(t_ray *ray, t_obj *obj, t_hit *hit)
{
	float		min_dist;
	t_obj	*closest_obj;
	t_hit		tmp_hit;

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
	if (closest_obj && closest_obj->pattern_num)
		hit->color = checkboard_color(closest_obj, hit->pHit);
	else if (closest_obj)
		hit->color = closest_obj->color;
	return (closest_obj);
}

t_color	light2rgb(t_colors *l)
{
	t_color	c;

	c.r = l->ambient.r + l->diffuse.r + l->specular.r;
	c.g = l->ambient.g + l->diffuse.g + l->specular.g;
	c.b = l->ambient.b + l->diffuse.b + l->specular.b;
	if (c.r > 1)
		c.r = 1;
	if (c.g > 1)
		c.g = 1;
	if (c.b > 1)
		c.b = 1;
	return (c);
}

t_color	raytrace(t_rt *rt, t_rays *r, int max_reflect)
{
	t_color		color;
	t_colors	colors;
	(void) max_reflect;

	ft_memset(&colors, 0, sizeof(colors));
	r->closest_obj = get_closest_obj(&r->prime_ray, rt->objs, &r->hit);
	if (!r->closest_obj)
		return (rt->bg_color);
	colors.ambient = r->hit.color;
	colors.ambient = add_light(colors.ambient, rt->ambient.color, rt->ambient.lighting);
	colors.is_shadow = shadow_ray(rt, r, rt->light);
	if (!colors.is_shadow)
		colors.diffuse = diffuse_light(r, rt->light);
	if (!colors.is_shadow)
		colors.specular = specular_light(r, rt->light);
	
	color = light2rgb(&colors);

	if (r->closest_obj->mirror > 0 && max_reflect--)
	{
		colors.reflect = reflection_ray(rt, r, max_reflect);
		color = mix_color(color, 1 - r->closest_obj->mirror,
			colors.reflect, r->closest_obj->mirror);
	}
	if (r->closest_obj->refract > 0 && max_reflect--)
	{
		colors.refract = refraction_ray(rt, r, max_reflect);
		color = mix_color(colors.refract, 0.7, color, 0.3);
	}
	return (color);
}

// t_color	raytrace(t_rt *rt, t_rays *r, int max_reflect)
// {
// 	t_color		color;
// 	t_colors	colors;

// 	r->closest_obj = get_closest_obj(&r->prime_ray, rt->objs, &r->hit);
// 	if (!r->closest_obj)
// 		return (rt->bg_color);
// 	color = lightrays(rt, r, rt->light);
// 	if (r->closest_obj->mirror > 0 && max_reflect--)
// 	{
// 		colors.reflect = reflection_ray(rt, r, max_reflect);
// 		color = mix_color(color, 1 - r->closest_obj->mirror,
// 			colors.reflect, r->closest_obj->mirror);
// 	}
// 	if (r->closest_obj->refract > 0 && max_reflect--)
// 	{
// 		color = mix_color(refraction_ray(rt, r, max_reflect),
// 			0.7, color, 0.3);
// 	}
// 	return (color);
// }

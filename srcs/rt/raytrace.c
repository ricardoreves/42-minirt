/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:22:36 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/17 04:55:54 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*get_closest_obj(t_ray *ray, t_object *obj, t_hit *hit)
{
	float		min_dist;
	t_object	*closest_obj;
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
	return (closest_obj);
}

typedef struct s_colors
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
}	t_colors;

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

t_color	lightrays(t_rt *rt, t_rays *r, t_object *closest_obj, t_light *light)
{
	t_colors	l;
	float		dot_p;
	t_vect		spec;

	ft_memset(&l, 0, sizeof(l));
	l.ambient = *color_obj(closest_obj);
	add_light(&l.ambient, rt->ambient.color, rt->ambient.lighting);
	r->shadowray.or = r->hit.pHit;
	r->shadowray.dir = vect_sub(r->hit.pHit, rt->light->coords);
	normalize(&r->shadowray.dir);
	ray_mul(&r->shadowray.or, &r->shadowray, 0.01);
	if (rt->event.mouse || (get_closest_obj(&r->shadowray, rt->objs, &r->shadow_hit)
		&& distance(r->shadowray.or, light->coords) > distance(r->shadow_hit.pHit, r->shadowray.or)))
		return (light2rgb(&l));
	l.diffuse = *color_obj(closest_obj);
	dot_p = dot_prod(r->shadowray.dir, r->hit.nHit);
	add_light(&l.diffuse, rt->light->color, rt->light->brightness * dot_p);
	spec = vect_mul(r->hit.nHit, dot_p * 2);
	spec = vect_sub(spec, r->shadowray.dir);
	dot_p = dot_prod(spec, r->prime_ray.dir);
	if (dot_p > EPSILON)
		dot_p = pow(dot_p, closest_obj->specn) * closest_obj->speckv;
	l.specular = newcolor(1, 1, 1);
	add_light(&l.specular, l.specular, rt->light->brightness * dot_p);
	return (light2rgb(&l));
}

t_color	refraction_ray(t_rt *rt, t_rays *r, int max_reflect, t_obj *obj)
{
	// t_color color;
	float	eta;
	(void) max_reflect;
	(void) rt;
	
	eta = 1 / obj->refract;
	r->prime_ray.or = r->hit.pHit;
	r->prime_ray.dir = refract_vect(r->prime_ray.dir, r->hit.nHit, eta);
	ray_mul(&r->prime_ray.or, &r->prime_ray, EPSILON);
	intersect(&r->prime_ray, obj, &r->hit);
	r->prime_ray.or = r->hit.pHit;
	r->hit.nHit = vect_inv(r->hit.nHit);
	r->prime_ray.dir = refract_vect(r->prime_ray.dir, r->hit.nHit, eta);
	return (raytrace(rt, r, max_reflect));
	// return (color);
}

t_color	raytrace(t_rt *rt, t_rays *r, int max_reflect)
{
	t_object	*closest_obj;
	t_color		color;
	t_color		reflect_color;
	t_rays		reflect;

	closest_obj = get_closest_obj(&r->prime_ray, rt->objs, &r->hit);
	if (!closest_obj)
		return (rt->bg_color);
	color = lightrays(rt, r, closest_obj, rt->light);
	if (closest_obj->mirror > 0 && max_reflect--)
	{
		reflect.prime_ray.or = r->hit.pHit;
		reflect.prime_ray.dir = reflect_vect(r->prime_ray.dir, r->hit.nHit);
		normalize(&reflect.prime_ray.dir);
		reflect_color = raytrace(rt, &reflect, max_reflect);
		color = mix_color(color, 1 - closest_obj->mirror,
				reflect_color, closest_obj->mirror);
	}
	if (closest_obj->mirror < 0 && max_reflect--)
	{
		color = mix_color(refraction_ray(rt, r, max_reflect, closest_obj),
			0.7, color, 0.3);
	}
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:22:36 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/15 04:16:36 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	shadow_rt(t_ray *ray, t_object *obj)
{
	t_hit	hit;

	while (obj)
	{
		if (intersect(ray, obj, &hit))
			return(TRUE);
		obj = obj->next;
	}
	return (FALSE);
}

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

int	light2rgb(t_colors *l)
{
	float	r;
	float	g;
	float	b;

	r = l->ambient.r + l->diffuse.r + l->specular.r;
	g = l->ambient.g + l->diffuse.g + l->specular.g;
	b = l->ambient.b + l->diffuse.b + l->specular.b;
	if (r > 1)
		r = 1;
	if (g > 1)
		g = 1;
	if (b > 1)
		b = 1;
	return (((int) (r * 255) << 16) + ((int) (g * 255) << 8) + (int) (b * 255));
}

int	lightrays(t_rt *rt, t_rays *r, t_object *closest_obj, t_light *light)
{
	t_colors	l;
	float		dot_p;
	t_vect		spec;

	ft_memset(&l, 0, sizeof(l));
	l.ambient = *color_obj(closest_obj);
	add_light(&l.ambient, &rt->ambient.color, rt->ambient.lighting);
	build_ray(&r->shadowray, &r->hit.pHit, vect_sub(&r->shadowray.dir, &r->hit.pHit, &rt->light.coords));
	ray_mul(&r->shadowray.or, &r->shadowray, 0.01); // to modify
	if (get_closest_obj(&r->shadowray, rt->objs, &r->shadow_hit)
		&& distance(&r->shadowray.or, &light->coords) > distance(&r->shadow_hit.pHit, &r->shadowray.or))
		return (light2rgb(&l));
	
	l.diffuse = *color_obj(closest_obj);
	dot_p = dot_prod(&r->shadowray.dir, &r->hit.nHit);
	add_light(&l.diffuse, &rt->light.color, rt->light.brightness * dot_p);
	
	vect_mul(&spec, &r->hit.nHit, dot_p * 2);
	vect_sub(&spec, &spec, &r->shadowray.dir);
	dot_p = dot_prod(&spec, &r->prime_ray.dir);
	dot_p = pow(dot_p, closest_obj->specn) * closest_obj->speckv;
	add_light(&l.specular, color_set(&l.specular, 1, 1, 1), rt->light.brightness * dot_p);
	return (light2rgb(&l));
}

int	raytrace(t_rt *rt, t_rays *r)
{
	t_object	*closest_obj;
	int			color;
	int			reflect_color;
	t_rays		reflect;

	closest_obj = get_closest_obj(&r->prime_ray, rt->objs, &r->hit);
	if (!closest_obj)
		return (BG_COLOR);
	color = lightrays(rt, r, closest_obj, &rt->light);
	if (closest_obj->mirror > 0)
	{
		reflect.prime_ray.or = r->hit.pHit;
		reflect.prime_ray.dir = reflect_vect(r->prime_ray.dir, r->hit.nHit);
		normalize(&reflect.prime_ray.dir);
		reflect_color = raytrace(rt, &reflect);
		color = mix_color(color, 1 - closest_obj->mirror, reflect_color, closest_obj->mirror);
	}
	return (color);
}

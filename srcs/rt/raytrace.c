/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:22:36 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/11 02:35:43 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	shadow_rt(t_ray *ray, t_object *obj)
{
	while (obj)
	{
		if (intersect(ray, obj, NULL, NULL))
			return(TRUE);
		obj = obj->next;
	}
	return (FALSE);
}

t_object	*get_closest_obj(t_ray *ray, t_object *obj, t_ray *nHit)
{
	float		min_dist;
	float		dist;
	t_object	*closest_obj;
	t_vect		tmp_nHit;
	t_vect		tmp_pHit;

	closest_obj = NULL;
	min_dist = INFINITY;
	while (obj)
	{
		if (intersect(ray, obj, &tmp_pHit, &tmp_nHit))
		{
			dist = distance(&ray->or, &tmp_pHit);
			if (dist < min_dist)
			{
				closest_obj = obj;
				min_dist = dist;
				nHit->or = tmp_pHit;
				nHit->dir = tmp_nHit;
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

typedef struct s_rays
{
	t_ray		camray;
	t_ray		lightray;
	t_ray		nHit;
}	t_rays;

int	lightrays(t_rt *rt, t_rays *r, t_object *closest_obj, t_light *light)
{
	t_colors	l;
	float		dot_p;
	t_vect		spec;
	t_ray		nHit;

	ft_memset(&l, 0, sizeof(l));
	
	l.ambient = *color_obj(closest_obj);
	add_light(&l.ambient, &rt->ambient.color, rt->ambient.lighting);
	build_ray(&r->lightray, &r->nHit.or, vectres(&r->lightray.dir, &r->nHit.or, &rt->light.coords));
	// if (shadow_rt(&r->lightray, rt->objs))
	
	if (get_closest_obj(&r->lightray, rt->objs, &nHit)
		&& distance(&r->lightray.or, &light->coords) > distance(&nHit.or, &r->lightray.or))
		return (light2rgb(&l));
	
	l.diffuse = *color_obj(closest_obj);
	dot_p = dot_prod(&r->lightray.dir, &r->nHit.dir);
	add_light(&l.diffuse, &rt->light.color, rt->light.brightness * dot_p);
	
	vect_mul(&spec, &r->nHit.dir, dot_p * 2);
	vectres(&spec, &spec, &r->lightray.dir);
	dot_p = dot_prod(&spec, &r->camray.dir);
	dot_p = pow(dot_p, closest_obj->specn) * closest_obj->speckv;
	add_light(&l.specular, color_set(&l.specular, 1, 1, 1), rt->light.brightness * dot_p);
	return (light2rgb(&l));
}

int	raytrace(t_rt *rt, int x, int y)
{
	t_rays		r;
	t_object	*closest_obj;
	int			color;

	build_camray(rt, &r.camray, x, y);
	closest_obj = get_closest_obj(&r.camray, rt->objs, &r.nHit);
	if (!closest_obj)
		return (BG_COLOR);
	color = lightrays(rt, &r, closest_obj, &rt->light);
	return (color);
}

// int	raytrace(t_rt *rt, int x, int y)
// {
// 	t_rays		r;
// 	t_colors	l;
// 	t_object	*closest_obj;
// 	float		dot_p;
// 	t_vect		spec;

// 	build_camray(rt, &r.camray, x, y);
// 	closest_obj = get_closest_obj(&r.camray, rt->objs, &r.nHit);
// 	if (!closest_obj)
// 		return (BG_COLOR);
// 	ft_memset(&l, 0, sizeof(l));
	
// 	l.ambient = *color_obj(closest_obj);
// 	add_light(&l.ambient, &rt->ambient.color, rt->ambient.lighting);
// 	build_ray(&r.lightray, &r.nHit.or, vectres(&r.lightray.dir, &r.nHit.or, &rt->light.coords));
// 	if (shadow_rt(&r.lightray, rt->objs))
// 		return (light2rgb(&l));
	
// 	l.diffuse = *color_obj(closest_obj);
// 	dot_p = dot_prod(&r.lightray.dir, &r.nHit.dir);
// 	add_light(&l.diffuse, &rt->light.color, rt->light.brightness * dot_p);
	
// 	vect_mul(&spec, &r.nHit.dir, dot_p * 2);
// 	vectres(&spec, &spec, &r.lightray.dir);
// 	dot_p = dot_prod(&spec, &r.camray.dir);
// 	dot_p = pow(dot_p, closest_obj->specn) * closest_obj->speckv;
// 	add_light(&l.specular, color_set(&l.specular, 1, 1, 1), rt->light.brightness * dot_p);
// 	return (light2rgb(&l));
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:22:36 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 05:08:32 by bgoncalv         ###   ########.fr       */
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
	if (closest_obj)
		hit->color = color_obj(closest_obj, hit);
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

void	handle_lights(t_rt *rt, t_rays *r, t_colors *colors)
{
	t_light	*l;
	colors->ambient = r->hit.color;
	colors->ambient = add_light(colors->ambient, rt->ambient.color, rt->ambient.lighting);
	l = rt->light;
	while (l)
	{
		colors->is_shadow = shadow_ray(rt, r, l);
		if (!colors->is_shadow)
			colors->diffuse = mix_color(colors->diffuse, 1, diffuse_light(r, l), 1);
		if (!colors->is_shadow)
			colors->specular = mix_color(colors->specular, 1, specular_light(r, l), 1);
		l = l->next;
	}
}

void	bump_normal(t_obj *obj, t_img *img, t_hit *hit)
{
	// t_vector	v;
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
	if (0 < x[0] && x[0] < img->width && 0 < y[0] && y[0] < img->height)
	{
		dst = img->addr
		+ (y[0] * img->line_length + x[0] * (img->bits_per_pixel / 8));
		c[0] = *((unsigned int *)dst) & 0xff;
		dst = img->addr
			+ (y[1] * img->line_length + x[1] * (img->bits_per_pixel / 8));
		c[1] = *((unsigned int *)dst) & 0xff;
	printf("%x, %x\n", c[0], c[1]);
	}
}

t_color	raytrace(t_rt *rt, t_rays *r, int max_reflect)
{
	t_color		color;
	t_colors	colors;

	ft_memset(&colors, 0, sizeof(colors));
	r->closest_obj = get_closest_obj(&r->prime_ray, rt->objs, &r->hit);
	if (!r->closest_obj)
		return (newcolor(0,0,0));
		// return (rt->bg_color);
	if (r->closest_obj->has_bump)
		bump_normal(r->closest_obj, &r->closest_obj->bump, &r->hit);
	handle_lights(rt, r, &colors);
	color = light2rgb(&colors);
	--max_reflect;
	if (r->closest_obj->mirror > 0 && max_reflect)
	{
		colors.reflect = reflection_ray(rt, r, max_reflect);
		color = mix_color(color, 1 - r->closest_obj->mirror,
			colors.reflect, r->closest_obj->mirror);
	}
	if (r->closest_obj->refract > 0 && max_reflect)
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

// 	ft_memset(&colors, 0, sizeof(colors));
// 	r->closest_obj = get_closest_obj(&r->prime_ray, rt->objs, &r->hit);
// 	if (!r->closest_obj)
// 		return (rt->bg_color);
// 	colors.ambient = r->hit.color;
// 	colors.ambient = add_light(colors.ambient, rt->ambient.color, rt->ambient.lighting);
// 	colors.is_shadow = shadow_ray(rt, r, rt->light);
// 	if (!colors.is_shadow)
// 		colors.diffuse = diffuse_light(r, rt->light);
// 	if (!colors.is_shadow)
// 		colors.specular = specular_light(r, rt->light);
// 	color = light2rgb(&colors);
// 	--max_reflect;
// 	if (r->closest_obj->mirror > 0 && max_reflect)
// 	{
// 		colors.reflect = reflection_ray(rt, r, max_reflect);
// 		color = mix_color(color, 1 - r->closest_obj->mirror,
// 			colors.reflect, r->closest_obj->mirror);
// 	}
// 	if (r->closest_obj->refract > 0 && max_reflect)
// 	{
// 		colors.refract = refraction_ray(rt, r, max_reflect);
// 		color = mix_color(colors.refract, 0.7, color, 0.3);
// 	}
// 	return (color);
// }

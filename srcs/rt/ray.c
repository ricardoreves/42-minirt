/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray->c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:48:55 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/24 15:57:27 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*get_closest_obj(t_ray *ray, t_object *obj, t_vect *pHit, t_vect *nHit)
{
	float		min_dist;
	float		dist;
	t_object	*closest_obj;
	t_vect		tmp_pHit;
	t_vect		tmp_nHit;

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
				vect_cpy(pHit, &tmp_pHit);
				vect_cpy(nHit, &tmp_nHit);
			}
		}
		obj = obj->next;
	}
	return (closest_obj);
}

t_vector	*ray_mul(t_vect *dst, t_ray *r, float t)
{
	dst->x = r->or.x + t * r->dir.x;
	dst->y = r->or.y + t * r->dir.y;
	dst->z = r->or.z + t * r->dir.z;
	return (dst);
}

void	build_ray(t_ray *ray, t_vect *or, t_vect *dir)
{
	ray->or.x = or->x;
	ray->or.y = or->y;
	ray->or.z = or->z;
	ray->dir.x = dir->x;
	ray->dir.y = dir->y;
	ray->dir.z = dir->z;
	normalize(&ray->dir);
}

void	build_camray(t_rt *rt, t_ray *ray, int x, int y)
{
	t_camera	*cam;

	cam = &rt->camera;
	vect_init(&ray->or, cam->coords.x, cam->coords.y, cam->coords.z);
	ray->dir.x = (2.0 * ((float) x + 0.5) / (float) rt->width - 1.0) * cam->scale * rt->aspectRatio;
	ray->dir.y = (1.0 - 2.0 * ((float) y + 0.5) / (float) rt->height) * cam->scale;
	vect_init(&ray->dir, ray->or.x + ray->dir.x, ray->or.y + ray->dir.y, ray->or.z + FOCAL_DIST); // careful need to be transform with matrix to world
	vectres(&ray->dir, &ray->or, &ray->dir);
	normalize(&ray->dir);
}

t_color	*add_light(t_color *color, t_color *light, float p2)
{
	color->r = color->r * light->r * p2;
	color->g = color->g * light->g * p2;
	color->b = color->b * light->b * p2;
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
	return (color);
}

typedef struct s_rays
{
	t_ray		camray;
	t_ray		shadow_ray;
	t_ray		nHit;
}	t_rays;

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

	r = 0;
	g = 0;
	b = 0;
	r += l->ambient.r;
	g += l->ambient.g;
	b += l->ambient.b;
	r += l->diffuse.r;
	g += l->diffuse.g;
	b += l->diffuse.b;
	r += l->specular.r;
	g += l->specular.g;
	b += l->specular.b;
	// r = l->ambient.r + l->diffuse.r + l->specular.r;
	// g = l->ambient.g + l->diffuse.g + l->specular.g;
	// b = l->ambient.b + l->diffuse.b + l->specular.b;
	if (r > 1)
		r = 1;
	if (g > 1)
		g = 1;
	if (b > 1)
		b = 1;
	return (((int) (r * 255) << 16) + ((int) (g * 255) << 8) + (int) (b * 255));
}

int	raytrace(t_rt *rt, int x, int y)
{
	t_rays		r;
	t_colors	l;
	t_object	*closest_obj;
	float		dot_p;

	build_camray(rt, &r.camray, x, y);
	closest_obj = get_closest_obj(&r.camray, rt->objs, &r.nHit.or, &r.nHit.dir);
	if (!closest_obj)
		return (BG_COLOR);
	ft_memset(&l, 0, sizeof(l));
	l.ambient = *color_obj(closest_obj);
	add_light(&l.ambient, &rt->ambient.color, rt->ambient.lighting);
	build_ray(&r.shadow_ray, &r.nHit.or, vectres(&r.shadow_ray.dir, &r.nHit.or, &rt->light.coords));
	if (get_closest_obj(&r.shadow_ray, rt->objs, &r.nHit.or, &r.nHit.dir))
		return (light2rgb(&l));
	l.diffuse = *color_obj(closest_obj);
	dot_p = dot_prod(&r.shadow_ray.dir, &r.nHit.dir);
	add_light(&l.diffuse, &rt->light.color, rt->light.brightness * dot_p);
	return (light2rgb(&l));
}

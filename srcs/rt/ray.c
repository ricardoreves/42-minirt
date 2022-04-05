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

	closest_obj = NULL;
	min_dist = INFINITY;
	while (obj)
	{
		if (intersect(ray, obj, pHit, nHit))
		{
			dist = distance(&ray->or, pHit);
			if (dist < min_dist)
			{
				closest_obj = obj;
				min_dist = dist;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
		intersect(ray, closest_obj, pHit, nHit);
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

t_color	*add_light(t_color *light, t_color *l2, float p2)
{
	light->r = light->r + l2->r * p2;
	light->g = light->g + l2->g * p2;
	light->b = light->b + l2->b * p2;
	if (light->r > 1)
		light->r = 1;
	if (light->g > 1)
		light->g = 1;
	if (light->b > 1)
		light->b = 1;
	return (light);
}

typedef struct s_rays
{
	t_ray		camray;
	t_ray		shadow_ray;
	t_ray		nHit;
}	t_rays;

int	raytrace(t_rt *rt, int x, int y)
{
	t_rays		r;
	t_color		light;
	t_object	*closest_obj;
	float		dot_p;

	build_camray(rt, &r.camray, x, y);
	closest_obj = get_closest_obj(&r.camray, rt->objs, &r.nHit.or, &r.nHit.dir);
	if (!closest_obj)
		return (BG_COLOR);
	light = rt->ambient.color;
	color_part(&light, rt->ambient.lighting);
	build_ray(&r.shadow_ray, &r.nHit.or, vectres(&r.shadow_ray.dir, &r.nHit.or, &rt->light.coords));
	if (get_closest_obj(&r.shadow_ray, rt->objs, &r.nHit.or, &r.nHit.dir))
		return (avg_color(color_obj(closest_obj), &light));
	dot_p = dot_prod(&r.shadow_ray.dir, &r.nHit.dir);
	add_light(&light, &rt->light.color, rt->light.brightness * dot_p);
	if (x ==1 && y == 1)
	{
		printf ("%f, %f, %f\n", light.r, light.g, light.b);
		printf ("%f, %f, %f\n", rt->ambient.color.r, rt->ambient.color.g, rt->ambient.color.b);
	}
	return (avg_color(color_obj(closest_obj), &light));
}


// int	raytrace(t_rt *rt, int x, int y)
// {
// 	t_rays		r;
// 	t_color		light;
// 	t_object	*closest_obj;
// 	float		dot_p;

// 	build_camray(rt, &r.camray, x, y);
// 	closest_obj = get_closest_obj(&r.camray, rt->objs, &r.nHit.or, &r.nHit.dir);
// 	if (!closest_obj)
// 		return (BG_COLOR);
// 	light = rt->ambient.color;
// 	color_part(&light, rt->ambient.lighting);
// 	build_ray(&r.shadow_ray, &r.nHit.or, vectres(&r.shadow_ray.dir, &r.nHit.or, &rt->light.coords));
// 	if (get_closest_obj(&r.shadow_ray, rt->objs, &r.nHit.or, &r.nHit.dir))
// 		return (avg_color(color_obj(closest_obj), &light));
// 	dot_p = dot_prod(&r.shadow_ray.dir, &r.nHit.dir);
// 	add_light(&light, &rt->light.color, rt->light.brightness * dot_p);
// 	return (avg_color(color_obj(closest_obj), &light));
// }

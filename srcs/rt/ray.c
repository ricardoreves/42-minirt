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

t_object	*get_closest_obj(t_ray *ray, t_object *obj, t_vect *or, t_vect *nHit)
{
	float		min_dist;
	float		dist;
	t_object	*closest_obj;

	closest_obj = NULL;
	min_dist = INFINITY;
	while (obj)
	{
		if (intersect(ray, obj, or, nHit))
		{
			dist = distance(&ray->or, or);
			if (dist < min_dist)
			{
				closest_obj = obj;
				min_dist = dist;
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

int	raytrace(t_rt *rt, int x, int y)
{
	t_ray		camray;
	t_ray		shadow_ray;
	t_ray		nHit;
	t_object	*closest_obj;
	t_color		light;

	build_camray(rt, &camray, x, y);
	closest_obj = get_closest_obj(&camray, rt->objs, &nHit.or, &nHit.dir);
	if (!closest_obj)
		return (0);
	light = rt->ambient.color;
	color_part(&light, rt->ambient.lighting);
	build_ray(&shadow_ray, &nHit.or, vectres(&shadow_ray.dir, &nHit.or, &rt->light.coords));
	if (get_closest_obj(&shadow_ray, rt->objs, &nHit.or, &nHit.dir))
		return (avg_color(color_obj(closest_obj), &light));
	add_light(&light, &rt->light.color, rt->light.brightness * dot_prod(&shadow_ray.dir, &nHit.dir));
	return (avg_color(color_obj(closest_obj), &light));
}

// int	raytrace(t_rt *rt, int x, int y)
// {
// 	t_ray		camray;
// 	t_ray		shadow_ray;
// 	t_ray		nHit;
// 	t_object	*closest_obj;

// 	build_camray(rt, &camray, x, y);
// 	closest_obj = get_closest_obj(&camray, rt->objs, &nHit.or, &nHit.dir);
// 	if (!closest_obj)
// 		return (0);
// 	build_ray(&shadow_ray, &nHit.or, vectres(&shadow_ray.dir, &nHit.or, &rt->light.coords));
// 	if (get_closest_obj(&shadow_ray, rt->objs, &nHit.or, &nHit.dir))
// 		return (color_mul(color_obj(closest_obj), 0.2));
// 	return (color_mul(color_obj(closest_obj),
// 			rt->light.brightness * dot_prod(&shadow_ray.dir, &nHit.dir)));
// }

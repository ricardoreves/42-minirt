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

// int	raytrace(t_ray *ray, t_rt *rt)
// {
// 	t_vect		or;
// 	t_vect		nHit;
// 	t_object	*closest_obj;

// 	vect_init(&ray->dir, ray->or.x + ray->dir.x, ray->or.y + ray->dir.y, ray->or.z + 1); // careful need to be transform with matrix to world
// 	vectres(&ray->dir, &ray->or, &ray->dir);
// 	normalize(&ray->dir);
// 	closest_obj = get_closest_obj(ray, rt->objs, &or, &nHit);
// 	if (!closest_obj)
// 		return (0);
// 	return (color2rgb(color_obj(closest_obj)));
// }

void	build_ray(t_ray *ray, t_vect *or, t_vect *dir)
{
	ray->or.x = or->x;
	ray->or.y = or->y;
	ray->or.z = or->z;
	ray->dir.x = dir->x;
	ray->dir.y = dir->y;
	ray->dir.z = dir->z;
}

void	build_camray(t_rt *rt, t_ray *ray, int x, int y)
{
	t_camera	*cam;

	cam = &rt->camera;
	vect_init(&ray->or, cam->coords.x, cam->coords.y, cam->coords.z);
	ray->dir.x = (2.0 * ((float) x + 0.5) / (float) rt->width - 1.0) * cam->scale * rt->aspectRatio;
	ray->dir.y = (1.0 - 2.0 * ((float) y + 0.5) / (float) rt->height) * cam->scale;
	vect_init(&ray->dir, ray->or.x + ray->dir.x, ray->or.y + ray->dir.y, ray->or.z + 1); // careful need to be transform with matrix to world
	vectres(&ray->dir, &ray->or, &ray->dir);
	normalize(&ray->dir);
}

int	raytrace(t_rt *rt, int x, int y)
{
	t_ray		nHit;
	t_object	*closest_obj;
	t_ray		shadow_ray;
	t_bool		in_shadow;
	t_ray		ray;

	build_camray(rt, &ray, x, y);
	closest_obj = get_closest_obj(&ray, rt->objs, &nHit.or, &nHit.dir);
	if (!closest_obj)
		return (0);
	shadow_ray.or = nHit.or;
	vectres(&shadow_ray.dir, &nHit.or, &rt->light.coords);
	normalize(&shadow_ray.dir);
	in_shadow = FALSE;
	if (get_closest_obj(&shadow_ray, rt->objs, &nHit.or, &nHit.dir))
		in_shadow = TRUE;
	if (in_shadow)
		return (color_mul(color_obj(closest_obj), 0.2));
	return (color_mul(color_obj(closest_obj),
			rt->light.brightness * dot_prod(&shadow_ray.dir, &nHit.dir)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:48:55 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 16:16:17 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	lookat(t_rt *rt)
{
	t_vect	forward;
	t_vect	right;
	t_vect	up;
	t_vect	tmp;

	tmp = vector(0, 1, 0);
	forward = rt->camera.orient;
	normalize(&forward);
	right = cross_prod(tmp, forward);
	up = cross_prod(forward, right);
	rt->cam_matrix[0][0] = right.x;
	rt->cam_matrix[0][1] = right.y;
	rt->cam_matrix[0][2] = right.z;
	rt->cam_matrix[1][0] = up.x;
	rt->cam_matrix[1][1] = up.y;
	rt->cam_matrix[1][2] = up.z;
	rt->cam_matrix[2][0] = forward.x;
	rt->cam_matrix[2][1] = forward.y;
	rt->cam_matrix[2][2] = forward.z;
}

t_vect	cam2world(float m[4][4], t_vect *v)
{
	t_vect	dst;

	dst.x = v->x * m[0][0] + v->y * m[1][0] + v->z * m[2][0];
	dst.y = v->x * m[0][1] + v->y * m[1][1] + v->z * m[2][1];
	dst.z = v->x * m[0][2] + v->y * m[1][2] + v->z * m[2][2];
	return (dst);
}

void	build_camray(t_rt *rt, t_ray *ray, float x, float y)
{
	t_camera	*cam;

	cam = &rt->camera;
	ray->or = vector(cam->coords.x, cam->coords.y, cam->coords.z);
	ray->dir.x = (2.0 * (x + 0.5) / (float) rt->width - 1.0)
		* cam->scale * rt->aspectratio;
	ray->dir.y = (1.0 - 2.0 * (y + 0.5) / (float) rt->height) * cam->scale;
	ray->dir.z = FOCAL_DIST;
	ray->dir = cam2world(rt->cam_matrix, &ray->dir);
	normalize(&ray->dir);
}

t_vect	*ray_mul(t_vect *dst, t_ray *r, float t)
{
	dst->x = r->or.x + t * r->dir.x;
	dst->y = r->or.y + t * r->dir.y;
	dst->z = r->or.z + t * r->dir.z;
	return (dst);
}

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
	ray->dir.x = (2.0 * ((float) x + 0.5) / (float) rt->width - 1.0)
					* cam->scale * rt->aspectRatio;
	ray->dir.y = (1.0 - 2.0 * ((float) y + 0.5) / (float) rt->height) * cam->scale;
	vect_init(&ray->dir, ray->or.x + ray->dir.x, ray->or.y + ray->dir.y
				, ray->or.z + FOCAL_DIST); // careful need to be transform with matrix to world
	vect_sub(&ray->dir, &ray->or, &ray->dir);
	normalize(&ray->dir);
}

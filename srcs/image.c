/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:17 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/25 01:16:42 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_img(t_img *img)
{
	ft_bzero(img->addr, WIN_HEIGHT * WIN_WIDTH * img->bits_per_pixel / 8);
}

void	putpixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (0 <= x && x < WIN_WIDTH && 0 <= y && y < WIN_HEIGHT)
	{
		dst = img->addr
			+ (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	gen_img(t_rt *rt)
{
	int			x;
	int			y;
	char		*pix;
	t_ray		ray;
	t_camera	*cam;

	y = 0;
	cam = &rt->camera;
	pix = rt->img.addr;
	vect_init(&ray.or, cam->coords.x, cam->coords.y, cam->coords.z);
	rt->camera.scale = tan(rt->camera.fov / 2 * M_PI /180);
	rt->aspectRatio = (float) rt->width / rt->height;     //careful when resizing if height > width
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray.dir.x = (2.0 * (((float) x + 0.5) / (float) rt->width) - 1.0) * rt->camera.scale * rt->aspectRatio;
			ray.dir.y = (1.0 - 2.0 * ((float) y + 0.5) / (float) rt->height) * rt->camera.scale;
			*(unsigned int *)pix = raytrace(&ray, rt);
			pix += rt->img.addr_incr;
			x++;
		}
		y++;
	}
}

			// if ((x == 300 || x == 749 || x == 1200) && (y == 100 || y == 599 || y == 1100))
			// {
			// printf("%f   %f   %f   len : %f\n", ray.dir.x, ray.dir.y, ray.dir.z, vectlen(&ray.dir));
			// }
			// printf("%f   %f    %f\n", ray.or.x, ray.or.y, ray.or.z);
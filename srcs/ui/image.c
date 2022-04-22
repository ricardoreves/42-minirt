/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:17 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 04:22:21 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	big_mix(t_color	c[9])
{
	t_color	r;
	int		i;

	i = 0;
	r = newcolor(0, 0, 0);
	while (i < 9)
	{
		r.r += c[i].r;
		r.g += c[i].g;
		r.b += c[i].b;
		i++;
	}
	r.r /= 9;
	r.g /= 9;
	r.b /= 9;
	return (color2rgb(r));
}

int	anti_aliasing(t_rt *rt, float x, float y)
{
	t_color	c[9];
	int		i;
	int		j;
	t_rays	r;

	y -= 0.33;
	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		x -= 0.99;
		while (j < 3)
		{
			build_camray(rt, &r.prime_ray, x, y);
			c[i * 3 + j] = raytrace(rt, &r, MAX_REFLECT);
			x += 0.33;
			j++;
		}
		y += 0.33;
		i++;
	}
	return (big_mix(c));
}

int	smart_rt(t_rt *rt, float x, float y)
{
	t_rays	r;

	if (rt->img.antialiasing_on && !rt->event.mouse)
		return (anti_aliasing(rt, x, y));
	build_camray(rt, &r.prime_ray, x, y);
	if (rt->event.mouse)
		return (color2rgb(raytrace(rt, &r, 0)));
	return (color2rgb(raytrace(rt, &r, MAX_REFLECT)));
}

void	gen_img(t_rt *rt)
{
	float		x;
	float		y;
	char		*pix;
	t_camera	*cam;

	y = 0;
	cam = &rt->camera;
	pix = rt->img.addr;
	cam->scale = tan(cam->fov / 2 * M_PI / 180);
	rt->aspectRatio = (float) rt->width / rt->height;
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	object_norm(rt);
	rt->bg_color = rgb2color(0x424242);
	lookat(rt);
	while (y < rt->height)
	{
		x = -1;
		while (++x < rt->width)
		{
			*(unsigned int *)pix = smart_rt(rt, x, y);
			pix += rt->img.addr_incr;
		}
		y++;
		display_progbar(rt, y, rt->height);
	}
}

void	render(t_rt *rt)
{
	gen_img(rt);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img.img, 0, 0);
	if (rt->display_info)
		put_info(rt);
}

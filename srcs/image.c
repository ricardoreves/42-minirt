/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:17 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/23 00:28:23 by bgoncalv         ###   ########.fr       */
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
	float		xdir;
	float		ydir;

	y = 0;
	pix = rt->img.addr;
	rt->camera.scale = tan(rt->camera.fov / 2 * M_PI /180);
	rt->aspectRatio = (float) rt->width / rt->height;     //careful when resizing if height > width
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			xdir = (2 * ((x + 0.5) / (float) rt->width) - 1) * rt->camera.scale * rt->aspectRatio;
			ydir = (1 - 2 * (y + 0.5) / (float) rt->height) * rt->camera.scale;
			*(unsigned int *)pix = raytrace(xdir, ydir, rt);
			pix += rt->img.addr_incr;
			x++;
		}
		y++;
	}
}

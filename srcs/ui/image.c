/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:17 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/03 20:38:33 by bgoncalv         ###   ########.fr       */
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
	t_camera	*cam;

	y = 0;
	cam = &rt->camera;
	pix = rt->img.addr;
	cam->scale = tan(cam->fov / 2 * M_PI / 180);
	rt->aspectRatio = (float) rt->width / rt->height;     //careful when resizing if height > width
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			*(unsigned int *)pix = raytrace(rt, x, y);
			pix += rt->img.addr_incr;
			x++;
		}
		y++;
	}
}

void	render(t_rt *rt)
{
	gen_img(rt);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img.img, 0, 0);
}

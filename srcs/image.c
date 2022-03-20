/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:17 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/20 02:54:58 by bgoncalv         ###   ########.fr       */
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

int	raytrace(int x, int y, t_rt *rt)
{
	int	color;

	(void) rt;
	
	color = x + y;
	return (color);
}

void	render_img(t_rt *rt)
{
	int		x;
	int		y;
	int		color;
	char	*dst;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			color = raytrace(x, y, rt);
			dst = rt->img.addr
			+ (y * rt->img.line_length + x * (rt->img.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}

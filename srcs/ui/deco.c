/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deco.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:46:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 04:33:03 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_deco(t_rt *rt, int width, int color)
{
	int	i;

	i = -1;
	while (++i < width * rt->width)
		*(unsigned int *)(rt->img.addr
				+ i * rt->img.bits_per_pixel / 8) = color;
	--i;
	while (++i < (width + 1) * rt->width)
		*(unsigned int *)(rt->img.addr
				+ i * rt->img.bits_per_pixel / 8) = 0xFFFFFF;
	i = rt->height * rt->width - (width + 1) * rt->width - 1;
	while (++i < rt->height * rt->width - width * rt->width)
		*(unsigned int *)(rt->img.addr
				+ i * rt->img.bits_per_pixel / 8) = 0xFFFFFF;
	while (++i < rt->height * rt->width)
		*(unsigned int *)(rt->img.addr
				+ i * rt->img.bits_per_pixel / 8) = color;
	mlx_string_put(rt->mlx, rt->mlx_win, 300, 250, 0XFF0000, "test\n");
}

void	put_info(t_rt *rt)
{
	int		c;
	void	*m;
	void	*w;

	c = 0;
	m = rt->mlx;
	w = rt->mlx_win;
	draw_deco(rt, DECO_WIDTH, COLORDEF);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img.img, 0, 0);
	mlx_string_put(m, w, rt->width - 200, rt->height - 45, c,
		"A to enable/cancel antialiasing");
	mlx_string_put(m, w, rt->width - 200, rt->height - 25, c,
		"I to hide info");
	mlx_string_put(m, w, rt->width - 200, rt->height - 5, c,
		"ESC to quit");
}

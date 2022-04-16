/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deco.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:46:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/16 18:44:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_deco(t_rt *rt, int width, int color)
{
	int	i;

	i = -1;
	while (++i < width * WIN_WIDTH)
		*(unsigned int *)(rt->img.addr
				+ i * rt->img.bits_per_pixel / 8) = color;
	--i;
	while (++i < (width + 1) * WIN_WIDTH)
		*(unsigned int *)(rt->img.addr
				+ i * rt->img.bits_per_pixel / 8) = 0xFFFFFF;
	i = WIN_HEIGHT * WIN_WIDTH - (width + 1) * WIN_WIDTH - 1;
	while (++i < WIN_HEIGHT * WIN_WIDTH - width * WIN_WIDTH)
		*(unsigned int *)(rt->img.addr
				+ i * rt->img.bits_per_pixel / 8) = 0xFFFFFF;
	while (++i < WIN_HEIGHT * WIN_WIDTH)
		*(unsigned int *)(rt->img.addr
				+ i * rt->img.bits_per_pixel / 8) = color;
	mlx_string_put(rt->mlx, rt->mlx_win, 300, 250, 0XFF0000, "test\n");
}

void	put_info(t_rt *rt)
{
	int		c;
	void	*m;
	void	*w;
	int		offy;

	c = 0;
	m = rt->mlx;
	w = rt->mlx_win;
	draw_deco(rt, DECO_WIDTH, COLORDEF);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img.img, 0, 0);
	offy = WIN_HEIGHT - DECO_WIDTH - 70;
	mlx_string_put(m, w, 30, WIN_HEIGHT - 45, c, "add sphere   : S + left click");
	mlx_string_put(m, w, 30, WIN_HEIGHT - 25, c, "add plane    : P + left click");
	mlx_string_put(m, w, 30, WIN_HEIGHT - 05, c, "add cylinder : C + left click (not yet)");
	mlx_string_put(m, w, WIN_WIDTH - 200, WIN_HEIGHT - 45, c, "A to enable/cancel antialiasing");
	mlx_string_put(m, w, WIN_WIDTH - 200, WIN_HEIGHT - 25, c, "I to hide info");
	mlx_string_put(m, w, WIN_WIDTH - 200, WIN_HEIGHT - 5, c, "ESC to quit");
}

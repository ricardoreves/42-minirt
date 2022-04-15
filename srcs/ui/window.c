/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:13 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/15 20:33:23 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_init(t_rt *rt, char *path)
{
	rt->mlx = mlx_init();
	rt->width = WIN_WIDTH;
	rt->height = WIN_HEIGHT;
	if (WIN_HEIGHT < WIN_WIDTH)
		rt->aspectRatio = WIN_WIDTH / WIN_HEIGHT;
	else
		rt->aspectRatio = WIN_HEIGHT / WIN_WIDTH;
	rt->mlx_win = mlx_new_window(rt->mlx, WIN_WIDTH, WIN_HEIGHT, "minirt");
	rt->path = path;
	rt->img.img = mlx_new_image(rt->mlx, WIN_WIDTH, WIN_HEIGHT);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
		&rt->img.line_length, &rt->img.endian);
	if (!rt->img.img)
	{
		rt_clear(rt);
		return ;
	}
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	hook_init(rt);
	rt->display_info = 0;
}

void	rt_clear(t_rt *rt)
{
	if (rt->mlx_win)
		mlx_destroy_window(rt->mlx, rt->mlx_win);
	if (rt->img.img)
		mlx_destroy_image(rt->mlx, rt->img.img);
	if (rt->mlx)
		ft_memdel(&rt->mlx);
	rt_free(rt);
}

void rt_free(t_rt *rt)
{
	if (rt)
	{	
		if (rt->light)
			free_lights(&rt->light);
		if (rt->objs)
			free_objects(&rt->objs);
		free(rt);
	}
}

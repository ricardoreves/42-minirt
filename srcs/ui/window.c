/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:13 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/20 15:22:52 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_init(t_rt *rt, char *path)
{
	rt->mlx = mlx_init();
	if (!rt->width)
		rt->width = (float) WIN_WIDTH;
	if (!rt->height)
		rt->height = (float) WIN_HEIGHT;
	if (rt->height < rt->width)
		rt->aspectRatio = rt->width / rt->height;
	else
		rt->aspectRatio = rt->height / rt->width;
	rt->mlx_win = mlx_new_window(rt->mlx, rt->width, rt->height, "minirt");
	rt->path = path;
	rt->img.img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
			&rt->img.line_length, &rt->img.endian);
	rt->img.antialiasing_on = ANTIALIASING_ON;
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

void	rt_free(t_rt *rt)
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

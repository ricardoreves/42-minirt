/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:13 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/20 15:32:34 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	handle_keydown(int key, t_rt *rt)
{
	if (key == ESCAPE_KEY)
	{
		rt_clear(rt);
		exit(EXIT_SUCCESS);
		return (0);
	}
	return (0);
}

static int	handle_no_event(t_rt *rt)
{
	(void) rt;
	return (0);
}

static int	exit_win(t_rt *rt)
{
	rt_clear(rt);
	exit(0);
	return (0);
}

void	rt_init(t_rt *rt, char *path)
{
	rt->mlx = mlx_init();
	rt->mlx_win = mlx_new_window(rt->mlx, WIN_WIDTH, WIN_HEIGHT, "minirt");
	rt->path = path;
	rt->img.img = mlx_new_image(rt->mlx, WIN_WIDTH, WIN_HEIGHT);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
		&rt->img.line_length, &rt->img.endian);
	hook_init(rt);
	if (!rt->img.img)
		rt_clear(rt);
	mlx_loop_hook(rt->mlx, handle_no_event, rt);
	mlx_hook(rt->mlx_win, ON_KEYDOWN, 0, handle_keydown, rt);
	mlx_hook(rt->mlx_win, ON_DESTROY, 0, exit_win, rt);
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
		if (rt->objs)
			free_objects(&rt->objs);
		free(rt);
	}
}

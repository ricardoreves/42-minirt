/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:41:37 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/07 02:59:27 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_win(t_rt *rt)
{
	rt_clear(rt);
	exit(0);
	return (0);
}

static int	handle_no_event(t_rt *rt)
{
	(void) rt;
	return (0);
}

void	hook_init(t_rt *rt)
{
	ft_memset(rt->event.key, 0, MAX_KEY);
	rt->event.mouse = 0;
	mlx_loop_hook(rt->mlx, handle_no_event, rt);
	mlx_hook(rt->mlx_win, ON_KEYDOWN, 1L<<0, handle_keydown, rt);
	mlx_hook(rt->mlx_win, ON_KEYUP, 1L<<1, handle_keyup, rt);
	mlx_hook(rt->mlx_win, ON_DESTROY, 0L, exit_win, rt);
	mlx_hook(rt->mlx_win, ON_MOUSEDOWN, 1L<<2, handle_mousedown, rt);
	mlx_hook(rt->mlx_win, ON_MOUSEUP, 1L<<3, handle_mouseup, rt);
	mlx_hook(rt->mlx_win, ON_MOUSEMOVE, 1L<<6, handle_mousemove, rt);
}

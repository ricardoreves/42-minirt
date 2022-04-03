/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:41:37 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/03 02:52:07 by bgoncalv         ###   ########.fr       */
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
	mlx_hook(rt->mlx_win, ON_KEYDOWN, 0, handle_keydown, rt);
	mlx_hook(rt->mlx_win, ON_KEYUP, 0, handle_keyup, rt);
	mlx_hook(rt->mlx_win, ON_DESTROY, 0, exit_win, rt);
	mlx_hook(rt->mlx_win, ON_MOUSEDOWN, 0, handle_mousedown, rt);
	mlx_hook(rt->mlx_win, ON_MOUSEUP, 0, handle_mouseup, rt);
	mlx_hook(rt->mlx_win, ON_MOUSEMOVE, 0, handle_mousemove, rt);
}

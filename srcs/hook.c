/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 04:57:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/20 06:03:35 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	msg_quit(char *s)
{
	ft_putendl_fd(s, 1);
	return (1);
}

int	handle_keydown(int key, t_rt *rt)
{
	if (key == KEY_EXIT)
		close_window(rt);
	return (0);
}

int	close_window(t_rt *rt)
{
	rt_clear(rt);
	exit(0);
	return (0);
}

void	hook_init(t_rt *rt)
{
	mlx_hook(rt->mlx_win, 2, 1L<<0, handle_keydown, rt);
	mlx_hook(rt->mlx_win, 17, 0L, close_window, rt);
}
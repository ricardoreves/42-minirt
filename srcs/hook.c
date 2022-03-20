/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 04:57:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/20 04:58:05 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	msg_quit(char *s)
{
	ft_putendl_fd(s, 1);
	return (EXIT_FAILURE);
}

int	handle_keydown(int key, t_rt *rt)
{
	if (key == 53)
	{
		close_window(rt);
		return (0);
	}
	return (0);
}

int	handle_no_event(t_rt *rt)
{
	(void) rt;
	return (0);
}

void	hook_init(t_rt *rt)
{
	mlx_loop_hook(rt->mlx, handle_no_event, rt);
	mlx_hook(rt->mlx_win, ON_KEYDOWN, 0, handle_keydown, rt);
}
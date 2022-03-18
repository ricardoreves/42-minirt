/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:31:39 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/18 03:53:56 by rpinto-r         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_rt	rt;

	if (argc != 2)
		return (msg_quit("Arg error : please enter an unique path as arg!"));
	rt_init(&rt, argv[1]);
	mlx_put_image_to_window(rt.mlx, rt.mlx_win, rt.img.img, 0, 0);
	mlx_loop(rt.mlx);
	return (0);
}
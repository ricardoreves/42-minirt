/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:31:39 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/19 01:54:55 by rpinto-r         ###   ########.fr       */
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
	t_rt *rt;

	rt = ft_calloc(sizeof(t_rt), 1);
	if (argc != 2)
		ft_putendl_fd("Error: please provide a scene file.", 2);
	else if (open_file(rt, argv[1]))
	{
		rt_init(rt, argv[1]);
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img.img, 0, 0);
		mlx_loop(rt->mlx);
	}
	rt_free(rt);
	return (0);
}

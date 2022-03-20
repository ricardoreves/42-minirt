/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:31:39 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/20 02:56:36 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	msg_quit(char *s)
{
	ft_putendl_fd(s, 1);
	return (EXIT_FAILURE);
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
		init_test(rt);
		render_img(rt);
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img.img, 0, 0);
		mlx_loop(rt->mlx);
	}
	rt_free(rt);
	return (0);
}

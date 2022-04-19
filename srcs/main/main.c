/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:31:39 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/20 00:55:24 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	msg_quit(char *s)
{
	ft_putendl_fd(s, 1);
	return (EXIT_FAILURE);
}

void	add_cone(t_rt *rt)
{
	t_obj	*obj;
	t_cone	*c;

	obj = create_object(rt, id_cone);
	c = &obj->object.cone;
	c->angle = 0.3;
	c->h = 30;
	c->coords = vector(50, 40, 95);
	c->orient = vector(0.5, -1, 0);
	obj->color = rgb2color(0x17f456);
	obj->second_color = rgb2color(0x17f456);
	c->color = rgb2color(0x78f456);
	obj->mirror = 0.8;
	obj->refract = 0;
	obj->pattern_num = 0;
}

int	main(int argc, char **argv)
{
	t_rt *rt;

	rt = ft_calloc(sizeof(t_rt), 1);
	if (argc != 2)
		show_error(USAGE_MESSAGE);
	else if (open_file(rt, argv[1]))
	{
		rt_init(rt, argv[1]);
		add_cone(rt);
		render(rt);
		mlx_loop(rt->mlx);
	}
	rt_free(rt);
	return (0);
}

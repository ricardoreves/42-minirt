/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:48:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/17 01:55:48 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_rt *rt;

	rt = ft_calloc(sizeof(t_rt), 1);
	if (argc != 2)
		ft_putendl_fd("Error: please provide a scene file.", 2);
	else if (open_file(rt, argv[1]))
	{
		rt_dump(rt);
	}
	rt_free(rt);
	return (0);
}

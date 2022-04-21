/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:32:38 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/21 14:32:11 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	show_parsing_error(t_rt *rt, char **arr, char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	if (rt->lnum)
	{
		ft_putstr_fd(" [line:", 2);
		ft_putnbr_fd(rt->lnum, 2);
		ft_putstr_fd(":param:", 2);
		ft_putnbr_fd(rt->pnum + 1, 2);
		ft_putstr_fd("]", 2);
	}
	ft_putendl_fd("", 2);
	free_array(arr);
	return (1);
}

int	show_error(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd("", 2);
	return (1);
}

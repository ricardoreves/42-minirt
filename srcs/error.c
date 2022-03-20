/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:32:38 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/20 04:29:35 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int show_parsing_error(char **arr, char *msg, int num)
{
	ft_putstr_fd("\033[1;31mError: ", 2);
	ft_putstr_fd(msg, 2);
	if (num)
	{
		ft_putstr_fd(" [line:", 2);
		ft_putnbr_fd(num, 2);
		ft_putstr_fd("]", 2);
	}
	ft_putendl_fd("\033[0m", 2);
	free_array(arr);
	return (1);
}

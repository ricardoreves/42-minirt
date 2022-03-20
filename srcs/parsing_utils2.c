/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:37:46 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/19 01:38:40 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_vector(char *str, t_vector *vect)
{
	char **tmp;
	int ret;

	ret = 0;
	tmp = ft_split(str, ',');
	if (array_length(tmp) != 3)
		ret = 1;
	else
	{
		vect->x = str_to_float(tmp[0]);
		vect->y = str_to_float(tmp[1]);
		vect->z = str_to_float(tmp[2]);
	}
	free_array(tmp);
	return (ret);
}

int parse_color(char *str, int *color)
{
	char **tmp;
	int ret;

	ret = 0;
	tmp = ft_split(str, ',');
	if (array_length(tmp) != 3)
		ret = 1;
	else
	{
		*color = str_to_int_color(tmp[0]);
		*color = (*color << 8) + str_to_int_color(tmp[1]);
		*color = (*color << 8) + str_to_int_color(tmp[2]);
	}
	free_array(tmp);
	return (ret);
}

int parse_float(char *str, float *num)
{
	if (!is_float(str))
		return (1);
	*num = str_to_float(str);
	return (0);
}

int parse_ulong(char *str, size_t *num)
{
	if (!is_ulong(str))
		return (1);
	*num = (size_t)ft_atoi(str);
	return (0);
}

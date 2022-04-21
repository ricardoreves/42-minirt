/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:37:46 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/20 02:57:58 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_vector(char *str, t_vect *vect)
{
	char	**tmp;
	int		ret;
	int		i;

	i = -1;
	ret = 0;
	tmp = ft_split(str, ',');
	while (tmp && tmp[++i])
		if (!is_float(tmp[i]))
			ret = 1;
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

int	parse_colors(char *str, t_color *color, t_color *color2)
{
	char	**tmp;
	int		ret;
	int		i;

	i = -1;
	ret = 0;
	tmp = ft_split(str, ';');
	if (array_length(tmp) < 1 || array_length(tmp) > 2)
		ret = 1;
	if (array_length(tmp) == 1)
		ret = parse_color(tmp[0], color);
	if (array_length(tmp) == 2)
		ret = parse_color(tmp[1], color2);
	free_array(tmp);
	return (ret);
}

int	parse_color(char *str, t_color *color)
{
	char	**tmp;
	int		ret;
	int		i;

	i = -1;
	ret = 0;
	tmp = ft_split(str, ',');
	while (tmp && tmp[++i])
		if (!is_ulong(tmp[i]))
			ret = 1;
	if (array_length(tmp) != 3)
		ret = 1;
	else
	{
		color->r = (float) str_to_int_color(tmp[0]) / 255;
		color->g = (float) str_to_int_color(tmp[1]) / 255;
		color->b = (float) str_to_int_color(tmp[2]) / 255;
	}
	free_array(tmp);
	return (ret);
}

int	parse_float(char *str, float *num)
{
	if (!is_float(str))
		return (1);
	*num = str_to_float(str);
	return (0);
}

int	parse_ulong(char *str, size_t *num)
{
	if (!is_ulong(str))
		return (1);
	*num = (size_t)ft_atoi(str);
	return (0);
}

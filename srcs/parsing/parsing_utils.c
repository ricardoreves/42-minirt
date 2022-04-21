/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:37:46 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/21 22:49:01 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_vector(char *str, t_vect *vect)
{
	int		i;
	int		ret;
	char	**nbrs;

	i = -1;
	ret = 0;
	nbrs = ft_split(str, ',');
	while (nbrs && nbrs[++i])
		if (!is_float(nbrs[i]))
			ret = 1;
	if (array_length(nbrs) != 3)
		ret = 1;
	else
	{
		vect->x = str_to_float(nbrs[0]);
		vect->y = str_to_float(nbrs[1]);
		vect->z = str_to_float(nbrs[2]);
	}
	free_array(nbrs);
	return (ret);
}

int	parse_colors(char *str, t_color *color, t_color *color2)
{
	int		i;
	int		ret;
	char	**colors;

	i = -1;
	ret = 0;
	colors = ft_split(str, ';');
	if (array_length(colors) < 1)
		ret = 1;
	while (colors && colors[++i])
	{
		if (i == 0)
			ret = parse_color(colors[0], color);
		if (i == 1)
			ret = parse_color(colors[1], color2);
	}
	free_array(colors);
	return (ret);
}

int	parse_color(char *str, t_color *color)
{
	int		i;
	int		ret;
	char	**rgb;

	i = -1;
	ret = 0;
	rgb = ft_split(str, ',');
	while (rgb && rgb[++i])
		if (!is_ulong(rgb[i]))
			ret = 1;
	if (array_length(rgb) != 3)
		ret = 1;
	else
	{
		color->r = (float) str_to_int_color(rgb[0]) / 255;
		color->g = (float) str_to_int_color(rgb[1]) / 255;
		color->b = (float) str_to_int_color(rgb[2]) / 255;
	}
	free_array(rgb);
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

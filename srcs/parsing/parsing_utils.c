/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 02:53:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/20 02:57:40 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_extra_params(t_obj *obj, char *str)
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
	if (array_length(tmp) != 6)
		ret = 1;
	else
	{
		obj->speckv = str_to_float(tmp[0]);
		obj->specn = str_to_float(tmp[1]);
		obj->mirror = str_to_float(tmp[2]);
		obj->refract = str_to_float(tmp[3]);
		obj->pattern_len = str_to_float(tmp[4]);
		obj->pattern_num = ft_atoi(tmp[5]);
	}
	free_array(tmp);
	return (ret);
}

int	has_line_valid_charset(char *line)
{
	int	i;

	i = -1;
	while (line && line[++i])
		if (ft_strchr(SCENE_CHARSET, line[i]) == 0)
			return (0);
	return (1);
}

char	*sanitize_line(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	free(tmp);
	return (line);
}
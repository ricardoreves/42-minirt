/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 02:53:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/22 05:04:55 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_imgpath(t_rt *rt, char *path, t_obj *obj, int type)
{
	int		fd;
	int		len;
	(void) rt;

	len = ft_strlen(path) - 4;
	if (len < 5 || ft_strncmp(path + len, ".xpm", 4) != 0)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	if (type == BUMP)
	{
		obj->bump.path = ft_strdup(path);
		obj->has_bump = TRUE;
	}
	if (type == TEXTURE)
	{
		obj->texture.path = ft_strdup(path);
		obj->has_texture = TRUE;
	}
	return (0);
}

int	parse_specular(char *str, t_obj *obj)
{
	int		i;
	int		ret;
	char	**params;

	i = -1;
	ret = 0;
	params = ft_split(str, ',');
	while (params && params[++i])
		if (!is_float(params[i]))
			ret = 1;
	if (array_length(params) != 2)
		ret = 1;
	else
	{
		obj->speckv = str_to_float(params[0]);
		obj->specn = str_to_float(params[1]);
	}
	free_array(params);
	return (ret);
}

int	parse_pattern(char *str, t_obj *obj)
{
	int		i;
	int		ret;
	char	**params;

	i = -1;
	ret = 0;
	params = ft_split(str, ',');
	if (array_length(params) != 2)
		ret = 1;
	if (!is_float(params[0]))
		ret = 1;
	if (!is_ulong(params[1]))
		ret = 1;
	if (!ret)
	{
		obj->pattern_len = str_to_float(params[0]);
		obj->pattern_num = ft_atoi(params[1]);
	}
	free_array(params);
	return (ret);
}

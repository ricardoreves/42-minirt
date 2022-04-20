/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 02:53:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/20 20:32:13 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int handle_params(t_param_id id, char *param)
// {
	
// }

// int	parse_extra_params(t_rt *rt, char *line, int num)
// {
// 	int 		i;
// 	char		**params;
// 	const int	fmt[2] = {id_float, id_float};

// 	i = 0;
// 	params = ft_split(line, ' ');
// 	if (array_length(params) != 3)
// 		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
// 	while (params && params[++i])
// 	{
// 		handle_params(fmt[i - 1], param[i]);
// 	}
// 	if (array_length(params) > 3)
// 	{
		
// 	}
	

// 	if (parse_float(params[1], &rt->width))
// 		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
// 	if (parse_float(params[2], &rt->height))
// 		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
// 	free_array(params);
// 	return (0);
// }

// int	parse_extra_params(t_obj *obj, char *str)
// {
// 	char	**tmp;
// 	int		ret;
// 	int		i;

// 	i = -1;
// 	params = ft_split(str, ' ');
// 	while (params && params[++i])
// 	{
// 		if (ft_strncmp(params[i], "spc", 3) == 0)
// 			return (parse_specular(rt, params[i] + 4, num));
// 		if (ft_strncmp(params[i], "mir", 3) == 0)
// 			return (parse_mirror(rt, params[i] + 4, num));
// 		if (ft_strncmp(params[i], "ref", 3) == 0)
// 			return (parse_refraction(rt, params[i] + 4, num));
// 		if (ft_strncmp(params[i], "pat", 3) == 0)
// 			return (parse_pattern(rt, params[i] + 4, num));
// 		if (ft_strncmp(params[i], "bum", 3) == 0)
// 			return (parse_bump(rt, params[i] + 4, num));
// 		if (ft_strncmp(params[i], "txm", 3) == 0)
// 			return (parse_texture(rt, params[i] + 4, num));
// 	}
// 	return (0);
// }

// int	parse_specular(t_obj *obj, char *str)
// {
// 	char	**tmp;
// 	int		ret;
// 	int		i;

// 	i = -1;
// 	ret = 0;
// 	tmp = ft_split(str, ',');
// 	while (tmp && tmp[++i])
// 		if (!is_float(tmp[i]))
// 			ret = 1;
// 	if (array_length(tmp) != 2)
// 		ret = 1;
// 	else
// 	{
// 		obj->speckv = str_to_float(tmp[0]);
// 		obj->specn = str_to_float(tmp[1]);
// 	}
// 	free_array(tmp);
// 	return (ret);
// }

// int	parse_specular(t_obj *obj, char *str)
// {
// 	char	**tmp;
// 	int		ret;
// 	int		i;

// 	i = -1;
// 	ret = 0;
// 	tmp = ft_split(str, ',');
// 	while (tmp && tmp[++i])
// 		if (!is_float(tmp[i]))
// 			ret = 1;
// 	if (array_length(tmp) != 6)
// 		ret = 1;
// 	else
// 	{
// 		obj->speckv = str_to_float(tmp[0]);
// 		obj->specn = str_to_float(tmp[1]);
// 		obj->mirror = str_to_float(tmp[2]);
// 		obj->refract = str_to_float(tmp[3]);
// 		obj->pattern_len = str_to_float(tmp[4]);
// 		obj->pattern_num = ft_atoi(tmp[5]);
// 	}
// 	free_array(tmp);
// 	return (ret);
// }

// int	parse_specular(t_obj *obj, char *str)
// {
// 	char	**tmp;
// 	int		ret;
// 	int		i;

// 	i = -1;
// 	ret = 0;
// 	tmp = ft_split(str, ',');
// 	while (tmp && tmp[++i])
// 		if (!is_float(tmp[i]))
// 			ret = 1;
// 	if (array_length(tmp) != 6)
// 		ret = 1;
// 	else
// 	{
// 		obj->speckv = str_to_float(tmp[0]);
// 		obj->specn = str_to_float(tmp[1]);
// 		obj->mirror = str_to_float(tmp[2]);
// 		obj->refract = str_to_float(tmp[3]);
// 		obj->pattern_len = str_to_float(tmp[4]);
// 		obj->pattern_num = ft_atoi(tmp[5]);
// 	}
// 	free_array(tmp);
// 	return (ret);
// }

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

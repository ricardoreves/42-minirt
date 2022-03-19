/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:31:28 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/19 00:57:30 by rpinto-r         ###   ########.fr       */
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

char *sanitize_line(char *line)
{
	int i;
	char *tmp;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	free(tmp);
	return (line);
}

int parse_ambient(t_rt *rt, char *line, int num)
{
	char **args;
	t_object *obj;
	t_ambient ambient;

	args = ft_split(line, ' ');
	if (array_length(args) != 3)
		return (show_parsing_error(args, ERR_TOO_FEW_OBJ_ARG, num));
	ft_bzero(&ambient, sizeof(t_ambient));
	ambient.id = id_ambient;
	if (parse_float(args[1], &ambient.lighting))
		return (show_parsing_error(args, ERR_NOT_A_FLOAT, num));
	if (parse_color(args[2], &ambient.color))
		return (show_parsing_error(args, ERR_TOO_FEW_COLOR_VAL, num));
	obj = create_object(rt);
	obj->id = id_ambient;
	obj->object.ambient = ambient;
	free_array(args);
	return (0);
}

int parse_camera(t_rt *rt, char *line, int num)
{
	char **args;
	t_camera camera;

	args = ft_split(line, ' ');
	if (array_length(args) != 4)
		return (show_parsing_error(args, ERR_TOO_FEW_OBJ_ARG, num));
	ft_bzero(&camera, sizeof(t_camera));
	camera.id = id_camera;
	if (parse_vector(args[1], &camera.coords))
		return (show_parsing_error(args, ERR_TOO_FEW_COORS_VAL, num));
	if (parse_vector(args[2], &camera.orient))
		return (show_parsing_error(args, ERR_TOO_FEW_ORIENT_VAL, num));
	if (parse_ulong(args[3], &camera.fov))
		return (show_parsing_error(args, ERR_NOT_A_ULONG, num));
	rt->camera = camera;
	free_array(args);
	return (0);
}

int parse_line(t_rt *rt, char *line, int num)
{

	printf("[line:%d]%s\n", num, line);
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_ambient(rt, line, num));
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_camera(rt, line, num));
	// if (ft_strncmp(line, "L", 1) == 0)
	// 	return (parse_light(rt, line, num));
	// if (ft_strncmp(line, "sp", 2) == 0)
	// 	return (parse_sphere(rt, line, num));
	// if (ft_strncmp(line, "pl", 2) == 0)
	// 	return (parse_plane(rt, line, num));
	// if (ft_strncmp(line, "cy", 2) == 0)
	// 	return (parse_cylinder(rt, line, num));
	return (0);
}
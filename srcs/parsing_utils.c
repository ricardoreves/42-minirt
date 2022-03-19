/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:39:44 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/19 01:51:20 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int parse_light(t_rt *rt, char *line, int num)
{
	char **args;
	t_object *obj;
	t_light light;

	args = ft_split(line, ' ');
	if (array_length(args) != 4)
		return (show_parsing_error(args, ERR_TOO_FEW_OBJ_ARG, num));
	ft_bzero(&light, sizeof(t_light));
	light.id = id_light;
	if (parse_vector(args[1], &light.coords))
		return (show_parsing_error(args, ERR_TOO_FEW_COORS_VAL, num));
	if (parse_float(args[2], &light.brightness))
		return (show_parsing_error(args, ERR_NOT_A_FLOAT, num));
	if (parse_color(args[3], &light.color))
		return (show_parsing_error(args, ERR_TOO_FEW_COLOR_VAL, num));
	obj = create_object(rt);
	obj->id = id_light;
	obj->object.light = light;
	free_array(args);
	return (0);
}

int parse_plane(t_rt *rt, char *line, int num)
{
	char **args;
	t_object *obj;
	t_plane plane;

	args = ft_split(line, ' ');
	if (array_length(args) != 4)
		return (show_parsing_error(args, ERR_TOO_FEW_OBJ_ARG, num));
	ft_bzero(&plane, sizeof(t_plane));
	plane.id = id_plane;
	if (parse_vector(args[1], &plane.coords))
		return (show_parsing_error(args, ERR_TOO_FEW_COORS_VAL, num));
	if (parse_vector(args[2], &plane.orient))
		return (show_parsing_error(args, ERR_TOO_FEW_ORIENT_VAL, num));
	if (parse_color(args[3], &plane.color))
		return (show_parsing_error(args, ERR_TOO_FEW_COLOR_VAL, num));
	obj = create_object(rt);
	obj->id = id_plane;
	obj->object.plane = plane;
	free_array(args);
	return (0);
}

int parse_sphere(t_rt *rt, char *line, int num)
{
	char **args;
	t_object *obj;
	t_sphere sphere;

	args = ft_split(line, ' ');
	if (array_length(args) != 4)
		return (show_parsing_error(args, ERR_TOO_FEW_OBJ_ARG, num));
	ft_bzero(&sphere, sizeof(t_sphere));
	sphere.id = id_sphere;
	if (parse_vector(args[1], &sphere.coords))
		return (show_parsing_error(args, ERR_TOO_FEW_COORS_VAL, num));
	if (parse_float(args[2], &sphere.diameter))
		return (show_parsing_error(args, ERR_NOT_A_FLOAT, num));
	if (parse_color(args[3], &sphere.color))
		return (show_parsing_error(args, ERR_TOO_FEW_COLOR_VAL, num));
	obj = create_object(rt);
	obj->id = id_sphere;
	obj->object.sphere = sphere;
	free_array(args);
	return (0);
}

int parse_cylinder(t_rt *rt, char *line, int num)
{
	char **args;
	t_object *obj;
	t_cylinder cylinder;

	args = ft_split(line, ' ');
	if (array_length(args) != 6)
		return (show_parsing_error(args, ERR_TOO_FEW_OBJ_ARG, num));
	ft_bzero(&cylinder, sizeof(t_cylinder));
	cylinder.id = id_cylinder;
	if (parse_vector(args[1], &cylinder.coords))
		return (show_parsing_error(args, ERR_TOO_FEW_COORS_VAL, num));
	if (parse_vector(args[2], &cylinder.orient))
		return (show_parsing_error(args, ERR_TOO_FEW_ORIENT_VAL, num));
	if (parse_float(args[3], &cylinder.diameter))
		return (show_parsing_error(args, ERR_NOT_A_FLOAT, num));
	if (parse_float(args[4], &cylinder.height))
		return (show_parsing_error(args, ERR_NOT_A_FLOAT, num));
	if (parse_color(args[5], &cylinder.color))
		return (show_parsing_error(args, ERR_TOO_FEW_COLOR_VAL, num));
	obj = create_object(rt);
	obj->id = id_cylinder;
	obj->object.cylinder = cylinder;
	free_array(args);
	return (0);
}
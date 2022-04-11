/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:39:44 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/10 00:41:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_ambient(t_rt *rt, char *line, int num)
{
	char **params;
	t_ambient ambient;

	params = ft_split(line, ' ');
	if (rt->ambient.id)
		return (show_parsing_error(params, ERR_TOO_MANY_AMBIENTS, num));
	if (array_length(params) != 3)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&ambient, sizeof(t_ambient));
	ambient.id = id_ambient;
	if (parse_float(params[1], &ambient.lighting))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	if (parse_color(params[2], &ambient.color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	rt->ambient = ambient;
	free_array(params);
	return (0);
}

int parse_light(t_rt *rt, char *line, int num)
{
	char **params;
	t_light light;

	params = ft_split(line, ' ');
	if (rt->light.id)
		return (show_parsing_error(params, ERR_TOO_MANY_LIGTHS, num));
	if (array_length(params) != 4)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&light, sizeof(t_light));
	light.id = id_light;
	if (parse_vector(params[1], &light.coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_float(params[2], &light.brightness))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	if (parse_color(params[3], &light.color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	rt->light = light;
	free_array(params);
	return (0);
}

int parse_plane(t_rt *rt, char *line, int num)
{
	char **params;
	t_object *obj;
	t_plane plane;

	params = ft_split(line, ' ');
	if (array_length(params) < 4)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&plane, sizeof(t_plane));
	plane.id = id_plane;
	if (parse_vector(params[1], &plane.coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_vector(params[2], &plane.orient))
		return (show_parsing_error(params, ERR_INVALID_NB_ORIENT, num));
	if (parse_color(params[3], &plane.color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	normalize(&plane.orient);
	obj = create_object(rt);
	obj->id = id_plane;
	obj->object.plane = plane;
	if (array_length(params) == 5 && parse_extra_params(obj, params[4])) 
		return (show_parsing_error(params, ERR_INVALID_EXTRA_PARAMS, num));
	free_array(params);
	return (0);
}

int parse_sphere(t_rt *rt, char *line, int num)
{
	char **params;
	t_object *obj;
	t_sphere sphere;

	params = ft_split(line, ' ');
	if (array_length(params) < 4)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&sphere, sizeof(t_sphere));
	sphere.id = id_sphere;
	if (parse_vector(params[1], &sphere.coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_float(params[2], &sphere.diameter))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	if (parse_color(params[3], &sphere.color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	obj = create_object(rt);
	obj->id = id_sphere;
	sphere.r2 = sphere.diameter * sphere.diameter * 0.25;
	obj->object.sphere = sphere;
	if (array_length(params) == 5 && parse_extra_params(obj, params[4])) 
		return (show_parsing_error(params, ERR_INVALID_EXTRA_PARAMS, num));
	free_array(params);
	return (0);
}

int parse_cylinder(t_rt *rt, char *line, int num)
{
	char **params;
	t_object *obj;
	t_cylinder cylinder;

	params = ft_split(line, ' ');
	if (array_length(params) < 6)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&cylinder, sizeof(t_cylinder));
	cylinder.id = id_cylinder;
	if (parse_vector(params[1], &cylinder.coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_vector(params[2], &cylinder.orient))
		return (show_parsing_error(params, ERR_INVALID_NB_ORIENT, num));
	if (parse_float(params[3], &cylinder.diameter) && parse_float(params[4], &cylinder.height))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	if (parse_color(params[5], &cylinder.color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	obj = create_object(rt);
	obj->id = id_cylinder;
	obj->object.cylinder = cylinder;
	if (array_length(params) == 7 && parse_extra_params(obj, params[6])) 
		return (show_parsing_error(params, ERR_INVALID_EXTRA_PARAMS, num));
	free_array(params);
	return (0);
}
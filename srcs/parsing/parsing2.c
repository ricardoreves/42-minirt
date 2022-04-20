/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:39:44 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/20 17:34:13 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane(t_rt *rt, char *line, int num)
{
	char		**params;
	t_obj		*obj;
	t_plane		plane;

	params = ft_split(line, ' ');
	if (array_length(params) < 4)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&plane, sizeof(t_plane));
	if (parse_vector(params[2], &plane.orient))
		return (show_parsing_error(params, ERR_INVALID_NB_ORIENT, num));
	normalize(&plane.orient);
	obj = create_object(rt, id_plane);
	if (parse_vector(params[1], &obj->coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_colors(params[3], &obj->color, &obj->second_color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	plane.coords = obj->coords;
	obj->object.plane = plane;
	if (array_length(params) == 5 && parse_extra_params(obj, params[4]))
		return (show_parsing_error(params, ERR_INVALID_EXTRA_PARAMS, num));
	free_array(params);
	return (0);
}

int	parse_sphere(t_rt *rt, char *line, int num)
{
	char		**params;
	t_obj		*obj;
	t_sphere	sphere;

	params = ft_split(line, ' ');
	if (array_length(params) < 4)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&sphere, sizeof(t_sphere));
	if (parse_float(params[2], &sphere.diameter))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	obj = create_object(rt, id_sphere);
	if (parse_vector(params[1], &obj->coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_colors(params[3], &obj->color, &obj->second_color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	sphere.coords = obj->coords;
	obj->object.sphere = sphere;
	if (array_length(params) == 5 && parse_extra_params(obj, params[4]))
		return (show_parsing_error(params, ERR_INVALID_EXTRA_PARAMS, num));
	free_array(params);
	return (0);
}

int	parse_cylinder(t_rt *rt, char *line, int num)
{
	char		**params;
	t_obj		*obj;
	t_cylinder	cylinder;

	params = ft_split(line, ' ');
	if (array_length(params) < 6)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&cylinder, sizeof(t_cylinder));
	if (parse_vector(params[2], &cylinder.orient))
		return (show_parsing_error(params, ERR_INVALID_NB_ORIENT, num));
	normalize(&cylinder.orient);
	if (parse_float(params[3], &cylinder.diameter)
		|| parse_float(params[4], &cylinder.height))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	obj = create_object(rt, id_cylinder);
	if (parse_vector(params[1], &obj->coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_colors(params[5], &obj->color, &obj->second_color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	cylinder.coords = obj->coords;
	obj->object.cylinder = cylinder;
	if (array_length(params) == 7 && parse_extra_params(obj, params[6]))
		return (show_parsing_error(params, ERR_INVALID_EXTRA_PARAMS, num));
	free_array(params);
	return (0);
}

int	parse_cone(t_rt *rt, char *line, int num)
{
	char	**params;
	t_obj	*obj;
	t_cone	cone;

	params = ft_split(line, ' ');
	if (array_length(params) < 7)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&cone, sizeof(t_cone));
	if (parse_vector(params[2], &cone.orient))
		return (show_parsing_error(params, ERR_INVALID_NB_ORIENT, num));
	normalize(&cone.orient);
	if (parse_float(params[3], &cone.h) || parse_float(params[4], &cone.h2)
		|| parse_float(params[5], &cone.angle))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	obj = create_object(rt, id_cone);
	if (parse_vector(params[1], &obj->coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_colors(params[6], &obj->color, &obj->second_color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	cone.coords = obj->coords;
	obj->object.cone = cone;
	if (array_length(params) == 8 && parse_extra_params(obj, params[7]))
		return (show_parsing_error(params, ERR_INVALID_EXTRA_PARAMS, num));
	free_array(params);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:31:28 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/20 15:17:19 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_camera(t_rt *rt, char *line, int num)
{
	char		**params;
	t_camera	camera;

	params = ft_split(line, ' ');
	if (rt->camera.id)
		return (show_parsing_error(params, ERR_TOO_MANY_CAMERAS, num));
	if (array_length(params) != 4)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	ft_bzero(&camera, sizeof(t_camera));
	camera.id = id_camera;
	if (parse_vector(params[1], &camera.coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_vector(params[2], &camera.orient))
		return (show_parsing_error(params, ERR_INVALID_NB_ORIENT, num));
	if (parse_ulong(params[3], &camera.fov))
		return (show_parsing_error(params, ERR_NOT_A_ULONG, num));
	normalize(&camera.orient);
	rt->camera = camera;
	free_array(params);
	return (0);
}

int	parse_ambient(t_rt *rt, char *line, int num)
{
	char		**params;
	t_ambient	ambient;

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

int	parse_light(t_rt *rt, char *line, int num)
{
	char	**params;
	t_light	*light;

	params = ft_split(line, ' ');
	if (array_length(params) != 4)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	light = create_light(rt);
	light->id = id_light;
	if (parse_vector(params[1], &light->coords))
		return (show_parsing_error(params, ERR_INVALID_NB_COORDS, num));
	if (parse_float(params[2], &light->brightness))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	if (parse_color(params[3], &light->color))
		return (show_parsing_error(params, ERR_INVALID_NB_COLORS, num));
	free_array(params);
	return (0);
}

int	parse_resolution(t_rt *rt, char *line, int num)
{
	char	**params;

	params = ft_split(line, ' ');
	if (array_length(params) != 3)
		return (show_parsing_error(params, ERR_INVALID_NB_PARAMS, num));
	if (parse_float(params[1], &rt->width))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	if (parse_float(params[2], &rt->height))
		return (show_parsing_error(params, ERR_NOT_A_FLOAT, num));
	free_array(params);
	return (0);
}

int	parse_line(t_rt *rt, char *line, int num)
{
	if (has_line_valid_charset(line))
	{
		if (ft_strncmp(line, "R", 1) == 0)
			return (parse_resolution(rt, line, num));
		if (ft_strncmp(line, "A", 1) == 0)
			return (parse_ambient(rt, line, num));
		if (ft_strncmp(line, "C", 1) == 0)
			return (parse_camera(rt, line, num));
		if (ft_strncmp(line, "L", 1) == 0)
			return (parse_light(rt, line, num));
		if (ft_strncmp(line, "sp", 2) == 0)
			return (parse_sphere(rt, line, num));
		if (ft_strncmp(line, "pl", 2) == 0)
			return (parse_plane(rt, line, num));
		if (ft_strncmp(line, "cy", 2) == 0)
			return (parse_cylinder(rt, line, num));
		if (ft_strncmp(line, "co", 2) == 0)
			return (parse_cone(rt, line, num));
	}
	else
		return (show_error(ERR_FORBIDDEN_CHAR));
	return (0);
}

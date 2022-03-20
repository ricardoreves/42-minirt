/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:31:28 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/20 16:02:09 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int has_line_valid_charset(char *line)
{
	int i;

	i = -1;
	while (line && line[++i])
		if (ft_strchr(SCENE_CHARSET, line[i]) == 0)
			return (0);
	return (1);
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

int parse_line(t_rt *rt, char *line, int num)
{
	// printf("[line:%d]%s\n", num, line);
	if (has_line_valid_charset(line))
	{
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
	}
	else
		return (show_error(ERR_FORBIDDEN_CHAR));
	return (0);
}
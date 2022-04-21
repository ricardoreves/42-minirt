/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:37:29 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/21 15:37:34 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_camera(t_rt *rt, char *line)
{
	int			i;
	char		**params;
	t_camera	camera;

	i = 0;
	params = ft_split(line, ' ');
	if (rt->camera.id)
		return (show_parsing_error(rt, params, ERR_TOO_MANY_CAMERAS));
	if (array_length(params) != 4)
		return (show_parsing_error(rt, params, ERR_INVALID_NB_PARAMS));
	ft_bzero(&camera, sizeof(t_camera));
	camera.id = id_camera;
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &camera.coords))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &camera.orient))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_ORIENT));
		if (i == 3 && parse_ulong(params[i], &camera.fov))
			return (show_parsing_error(rt, params, ERR_NOT_A_ULONG));
	}
	normalize(&camera.orient);
	rt->camera = camera;
	free_array(params);
	return (0);
}

int	parse_ambient(t_rt *rt, char *line)
{
	int			i;
	char		**params;
	t_ambient	ambient;

	i = 0;
	params = ft_split(line, ' ');
	if (rt->ambient.id)
		return (show_parsing_error(rt, params, ERR_TOO_MANY_AMBIENTS));
	if (array_length(params) != 3)
		return (show_parsing_error(rt, params, ERR_INVALID_NB_PARAMS));
	ft_bzero(&ambient, sizeof(t_ambient));
	ambient.id = id_ambient;
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_float(params[i], &ambient.lighting))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 2 && parse_color(params[i], &ambient.color))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	rt->ambient = ambient;
	free_array(params);
	return (0);
}

int	parse_light(t_rt *rt, char *line)
{
	int		i;
	char	**params;
	t_light	*light;

	i = 0;
	params = ft_split(line, ' ');
	if (array_length(params) != 4)
		return (show_parsing_error(rt, params, ERR_INVALID_NB_PARAMS));
	light = create_light(rt);
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &light->coords))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_float(params[i], &light->brightness))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 3 && parse_color(params[i], &light->color))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	free_array(params);
	return (0);
}

int	parse_resolution(t_rt *rt, char *line)
{
	int		i;
	char	**params;

	i = 0;
	params = ft_split(line, ' ');
	if (array_length(params) != 3)
		return (show_parsing_error(rt, params, ERR_INVALID_NB_PARAMS));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_float(params[i], &rt->width))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 2 && parse_float(params[i], &rt->height))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
	}
	free_array(params);
	return (0);
}

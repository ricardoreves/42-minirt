/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_shapes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:39:44 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/22 23:35:03 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane(t_rt *rt, char **params, t_obj *obj)
{
	int		i;
	t_plane	plane;

	i = 0;
	ft_bzero(&plane, sizeof(t_plane));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &obj->coords))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &plane.orient))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_ORIENT));
		if (i == 3 && parse_colors(params[i], &obj->color, &obj->color2))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	normalize(&plane.orient);
	plane.coords = obj->coords;
	obj->object.plane = plane;
	return (0);
}

int	parse_sphere(t_rt *rt, char **params, t_obj *obj)
{
	int			i;
	t_sphere	sphere;

	i = 0;
	ft_bzero(&sphere, sizeof(t_sphere));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &obj->coords))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_float(params[i], &sphere.diameter))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 3 && parse_colors(params[i], &obj->color, &obj->color2))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	sphere.coords = obj->coords;
	obj->object.sphere = sphere;
	return (0);
}

int	parse_cylinder(t_rt *rt, char **params, t_obj *obj)
{
	int			i;
	t_cylinder	cylinder;

	i = 0;
	ft_bzero(&cylinder, sizeof(t_cylinder));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &obj->coords))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &cylinder.orient))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_ORIENT));
		if (i == 3 && parse_float(params[i], &cylinder.diameter))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 4 && parse_float(params[i], &cylinder.height))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 5 && parse_colors(params[i], &obj->color, &obj->color2))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}	
	normalize(&cylinder.orient);
	cylinder.coords = obj->coords;
	obj->object.cylinder = cylinder;
	return (0);
}

int	parse_cone(t_rt *rt, char **params, t_obj *obj)
{
	int		i;
	t_cone	cone;

	i = 0;
	ft_bzero(&cone, sizeof(t_cone));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &obj->coords))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &cone.orient))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_ORIENT));
		if (i == 3 && parse_float(params[i], &cone.h))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 4 && parse_float(params[i], &cone.h2))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 5 && parse_float(params[i], &cone.angle))
			return (show_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 6 && parse_colors(params[i], &obj->color, &obj->color2))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	normalize(&cone.orient);
	cone.coords = obj->coords;
	obj->object.cone = cone;
	return (0);
}

int	parse_triangle(t_rt *rt, char **params, t_obj *obj)
{
	int			i;
	t_triangle	triangle;

	i = 0;
	ft_bzero(&triangle, sizeof(t_triangle));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &triangle.c[0]))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &triangle.c[1]))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 3 && parse_vector(params[i], &triangle.c[2]))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 4 && parse_colors(params[i], &obj->color, &obj->color2))
			return (show_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}	
	triangle.color = obj->color;
	obj->object.triangle = triangle;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:48:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/19 00:28:25 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void push_object(t_object *obj, t_object **objs)
{
	t_object *tmp;

	if (!(*objs))
		*objs = obj;
	else
	{
		tmp = *objs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
}

t_object *create_object(t_rt *rt)
{
	t_object *obj;

	obj = ft_calloc(sizeof(t_object), 1);
	push_object(obj, &rt->objs);
	rt->num_objs++;
	return (obj);
}

void free_objects(t_object **objs)
{
	t_object *tmp;
	t_object *obj;

	obj = *objs;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	*objs = 0;
}

char *sanitize_line(char *line, int lineno)
{
	int i;
	char *tmp;
	(void)lineno;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	free(tmp);
	return (line);
}

void parse_ambient(t_rt *rt, char *line, int lineno)
{
	char **args;
	t_object *obj;
	t_ambient ambient;

	args = ft_split(line, ' ');
	if (array_length(args) != 3)
	{
		free_array(args);
		show_parsing_error("too few arguments", lineno);
	}
	
	ft_bzero(&ambient, sizeof(t_ambient));
	ambient.id = id_ambient;
	ambient.lighting = str_to_float(args[1]);
	str_to_color(args[2], &ambient.color);

	obj = create_object(rt);
	obj->id = id_ambient;
	obj->object.ambient = ambient;
	print_array(args);
	free_array(args);
}

void parse_camera(t_rt *rt, char *line, int lineno)
{
	char **args;
	t_camera camera;

	args = ft_split(line, ' ');
	if (array_length(args) != 4)
	{
		free_array(args);
		show_parsing_error("too few arguments", lineno);
	}
	
	ft_bzero(&camera, sizeof(t_camera));
	camera.id = id_camera;
	str_to_vector(args[1], &camera.coords);
	str_to_vector(args[2], &camera.orient);
	camera.fov = (size_t)ft_atoi(args[3]);

	rt->camera = camera;
	print_array(args);
	free_array(args);
}

int parse_line(t_rt *rt, char *line, int lineno)
{
	if (ft_strncmp(line, "A", 1) == 0)
		parse_ambient(rt, line, lineno);
	if (ft_strncmp(line, "C", 1) == 0)
		parse_camera(rt, line, lineno);
	// if (ft_strncmp(line, "L", 1) == 0)
	// 	parse_light(rt, line, lineno);
	// if (ft_strncmp(line, "sp", 2) == 0)
	// 	parse_sphere(rt, line, lineno);
	// if (ft_strncmp(line, "pl", 2) == 0)
	// 	parse_plane(rt, line, lineno);
	// if (ft_strncmp(line, "cy", 2) == 0)
	// 	parse_cylinder(rt, line, lineno);
	return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int lineno;
	int fd;
	char *line;
	t_rt *rt;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}

	lineno = 1;
	rt = ft_calloc(sizeof(t_rt), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		line = sanitize_line(line, lineno);
		parse_line(rt, line, lineno);
		printf("[%d]%s\n", lineno, line);
		lineno++;
		free(line);
	}
	close(fd);

	printf("%d\n", rt->objs->id);
	printf("%d\n", rt->objs->object.ambient.id);
	printf("%d\n", rt->objs->object.ambient.color);
	printf("%f\n", rt->objs->object.ambient.lighting);

	printf("%d\n", rt->camera.id);
	printf("%f\n", rt->camera.coords.x);
	printf("%f\n", rt->camera.orient.x);
	printf("%ld\n", rt->camera.fov);

	free_objects(&rt->objs);
	free(rt);

	// rgb = 65536 * red + 256 * green + blue;
	// printf("color: %d %ld\n", rgb, (size_t)ft_atoi("-245"));

	// printf("%f %f\n", 0.0245000, str_to_float("0.0245000"));
	// printf("%f %f\n", 1.000846, str_to_float("1.000846"));
	// printf("%f %f\n", 10.011000, str_to_float("10.011000"));
	// printf("%f %f\n", 100.011280, str_to_float("100.011280"));
	// printf("%f %f\n", -0.466130, str_to_float("-0.466130"));
	// printf("%f %f\n", -2.000846, str_to_float("-2.000846"));
	// printf("%f %f\n", -20.011000, str_to_float("-20.011000"));
	return (0);
}
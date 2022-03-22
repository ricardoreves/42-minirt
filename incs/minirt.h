/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:42:00 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/23 00:32:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1500
# define WIN_HEIGHT 1200
# ifdef __APPLE__
#  define ESCAPE_KEY 53
# elif defined __unix__
#  define ESCAPE_KEY 65307
# endif
# define USAGE_MESSAGE "Usage: ./minirt scenes/mandatory.c"
# define SCENE_CHARSET "ACLsplcy0123456789-,. \n"
# define ERR_FILE_NOT_FOUND "file not found"
# define ERR_IS_NOT_RT_FILE "isn't a rt file"
# define ERR_FORBIDDEN_CHAR "contain forbidden character"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# include "mlx.h"
# include "libft.h"
# include "objects.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		addr_incr;
}	t_img;

typedef struct s_rt
{
	char		*path;
	int			width;
	int			height;
	float		aspectRatio;
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_camera	camera;
	t_object	*objs;
	size_t		num_objs;
}	t_rt;

/* test.c */
void	init_test(t_rt *rt);

/* main.c */
int		msg_quit(char *s);

/* window.c */
void	rt_init(t_rt *rt, char *path);
void	rt_clear(t_rt *rt);
int		close_window(t_rt *rt);
void	rt_free(t_rt *rt);

/* image.c*/
void	clear_img(t_img *img);
void	putpixel(t_img *img, int x, int y, int color);
void	gen_img(t_rt *rt);

/* ray.c */
int		raytrace(float x, float y, t_rt *rt);

/* vector.c */
void	vectcpy(t_vector *dst, t_vector *src);
void	vectres(t_vector *dst, t_vector *a, t_vector *b);
t_vector	*normalize(t_vector *v);

/* array_utils.c */
void	free_array(char *arr[]);
void	print_array(char *arr[]);
int		array_length(char *arr[]);

/* convert.c */
float	str_to_float(char *str);
int		str_to_int_color(char *str);

/* error.c */
int 	show_parsing_error(char **arr, char *msg, int num);
int 	show_error(char *msg);

/* object_utils.c */
void 	push_object(t_object *obj, t_object **objs);
t_object *create_object(t_rt *rt);
void 	free_objects(t_object **objs);

/* file.c */
int 	read_file(t_rt *rt, int fd);
int 	open_file(t_rt *rt, char *path);
int	 	is_rt_file(char *path);

/* number.c */
int is_float(char *str);
int is_ulong(char *str);

/* parsing.c */
char *sanitize_line(char *line);
int parse_line(t_rt *rt, char *line, int num);
int parse_vector(char *str, t_vector *vect);
int parse_color(char *str, int *color);
int parse_float(char *str, float *num);
int parse_ulong(char *str, size_t *num);
int parse_ambient(t_rt *rt, char *line, int num);
int parse_camera(t_rt *rt, char *line, int num);
int parse_light(t_rt *rt, char *line, int num);
int parse_plane(t_rt *rt, char *line, int num);
int parse_sphere(t_rt *rt, char *line, int num);
int parse_cylinder(t_rt *rt, char *line, int num);

/* debug.c */
void rt_dump(t_rt *rt);

#endif
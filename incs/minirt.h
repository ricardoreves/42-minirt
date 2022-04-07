/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:42:00 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/07 21:29:27 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define FOCAL_DIST 0.5
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define DECO_WIDTH 60
# define COLORDEF 0x81A1C1
# define BG_COLOR 0x000000
# define MAX_KEY 65535
# ifdef __APPLE__
#  define ESCAPE_KEY 53
#  define S_KEY 1
#  define P_KEY 35
#  define L_KEY 37
#  define C_KEY 5
#  define D_KEY 2
#  define I_KEY 34
#  define LEFT_CLICK 1
#  define RIGHT_CLICK 2
# elif defined __unix__
#  define ESCAPE_KEY 65307
#  define S_KEY 115
#  define P_KEY 112
#  define L_KEY 108
#  define C_KEY 99
#  define D_KEY 100
#  define I_KEY 105
#  define LEFT_CLICK 1
#  define RIGHT_CLICK 2
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
# include "ui.h"
# include "parsing.h"

typedef enum e_bool {FALSE, TRUE}	t_bool;
typedef t_vector					t_vect;
typedef t_object					t_obj;

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

typedef struct s_event
{
	int		x;
	int		y;
	int		lastx;
	int		lasty;
	int		key[MAX_KEY];
	int		mouse;
	t_obj	*selection;
}	t_event;

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
	t_ambient	ambient;
	t_light		light;
	t_object	*objs;
	size_t		num_objs;
	t_event		event;
	int			display_info;
}	t_rt;

/* window.c */
void	rt_init(t_rt *rt, char *path);
void	rt_clear(t_rt *rt);
int		close_window(t_rt *rt);
void	rt_free(t_rt *rt);

/* event.c */
void	hook_init(t_rt *rt);
int		exit_win(t_rt *rt);

/* keyboard */
int		handle_keydown(int key, t_rt *rt);
int		handle_keyup(int key, t_rt *rt);

/* mouse */
int		handle_mousedown(int button, int x, int y, t_rt *rt);
int		handle_mouseup(int button, int x, int y, t_rt *rt);
int		handle_mousemove(int x, int y, t_rt *rt);

/* deco.c */
void	draw_deco(t_rt *rt, int width, int color);
void	put_info(t_rt *rt);

/* test.c */
void	init_test(t_rt *rt);

/* main.c */
int		msg_quit(char *s);

/* image.c*/
void	clear_img(t_img *img);
void	putpixel(t_img *img, int x, int y, int color);
void	gen_img(t_rt *rt);
void	render(t_rt *rt);

/* ray.c */
int		raytrace(t_rt *rt, int x, int y);
t_obj	*get_closest_obj(t_ray *ray, t_object *obj, t_vect *pHit, t_vect *nHit);
void	build_camray(t_rt *rt, t_ray *ray, int x, int y);
void	build_ray(t_ray *ray, t_vect *or, t_vect *dir);
t_vect	*ray_mul(t_vect *dst, t_ray *r, float t);

/* inter.c */
int		intersect(t_ray *ray, t_object *obj, t_vect *pHit, t_vect *nHit);

/* vector.c */
t_vect	*vect_init(t_vector *v, float x, float y, float z);
float	vectlen(t_vector *v);
t_vect	*vectres(t_vector *dst, t_vector *a, t_vector *b);
t_vect	*vect_add(t_vector *dst, t_vector *a, t_vector *b);
t_vect	*vect_mul(t_vect *dst, t_vect *v, float f);
t_vect	*normalize(t_vector *v);
float	dot_prod(t_vector *v1, t_vector *v2);
float	distance(t_vect *a, t_vect *b);
t_vect	*vect_inv(t_vect *v);

/* color.c */
int		color2rgb(t_color *c);
t_color	*color_obj(t_obj *obj);
t_color	*color_part(t_color *c, float p);
t_color *color_set(t_color *color, float r, float g, float b);
t_color	*add_light(t_color *color, t_color *light, float p2);

/* object_utils.c */
void	push_object(t_object *obj, t_object **objs);
t_obj	*create_object(t_rt *rt);
void	free_objects(t_object **objs);

/* file.c */
int		read_file(t_rt *rt, int fd);
int		open_file(t_rt *rt, char *path);
int		is_rt_file(char *path);
int		is_invalid_file(t_rt *rt);

/* number.c */
int		is_float(char *str);
int		is_ulong(char *str);

/* parsing.c */
char	*sanitize_line(char *line);
int		parse_line(t_rt *rt, char *line, int num);
int		parse_vector(char *str, t_vector *vect);
int		parse_extra_params(t_object *obj, char *str);
// int		parse_color(char *str, int *color);
int		parse_color(char *str, t_color *color);
int		parse_float(char *str, float *num);
int		parse_ulong(char *str, size_t *num);
int		parse_ambient(t_rt *rt, char *line, int num);
int		parse_camera(t_rt *rt, char *line, int num);
int		parse_light(t_rt *rt, char *line, int num);
int		parse_plane(t_rt *rt, char *line, int num);
int		parse_sphere(t_rt *rt, char *line, int num);
int		parse_cylinder(t_rt *rt, char *line, int num);

/* array_utils.c */
void	free_array(char *arr[]);
void	print_array(char *arr[]);
int		array_length(char *arr[]);

/* convert.c */
float	str_to_float(char *str);
int		str_to_int_color(char *str);

/* error.c */
int		show_parsing_error(char **params, char *msg, int num);
int		show_error(char *msg);

/* debug.c */
void	rt_dump(t_rt *rt);

#endif
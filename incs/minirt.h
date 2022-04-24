/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:42:00 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/24 07:46:18 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define EPSILON 0.0001
# define SPECULAR_KV 0.5
# define SPECULAR_N 20
# define MIRROR 0.0
# define REFRACT 0.0
# define PATTERN_LEN 0.0
# define PATTERN_NUM 0
# define FOCAL_DIST 0.5
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define DECO_WIDTH 60
# define COLORDEF 0x81A1C1
# define BG_COLOR 0xCFCFFF
# define WHITE 0x00FFFFFF
# define BLACK 0x0000000
# define DARKGREY 0x333333
# define MAX_KEY 65535
# define MAX_REFLECT 5
# define ANTIALIASING_ON FALSE
# define PROGBAR_TEXT_W 90
# define PROGBAR_TEXT_H 12
# define PROGBAR_W 150
# define PROGBAR_H 5
# define MAX_THREADS 10
# ifdef __APPLE__
#  define ESC_KEY 53
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define C_KEY 5
#  define I_KEY 34
#  define P_KEY 35
#  define L_KEY 37
#  define LEFT_CLICK 1
#  define RIGHT_CLICK 2
# elif defined __unix__
#  define ESC_KEY 65307
#  define A_KEY 97
#  define S_KEY 115
#  define P_KEY 112
#  define L_KEY 108
#  define C_KEY 99
#  define D_KEY 100
#  define I_KEY 105
#  define LEFT_CLICK 1
#  define RIGHT_CLICK 2
# endif
# define MSG_USAGE "Usage: ./minirt scenes/mandatory.c"
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
# include <pthread.h>
# include <sys/time.h>

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

typedef struct s_progbar
{
	int		bar_x;
	int		bar_y;
	int		text_x;
	int		text_y;
	int		prog_x;
	int		prog_y;	
	int		perc_x;
	int		perc_y;
	int		prog;
	char	*s_prog;
}	t_progbar;

enum {
	BUMP = 0,
	TEXTURE = 1
};

typedef struct s_event
{
	int		x;
	int		y;
	int		lastx;
	int		lasty;
	int		key[MAX_KEY];
	int		mouse;
	t_obj	*selection;
	t_bool	torender;
}	t_event;

typedef struct s_rt
{
	char		*path;
	float		width;
	float		height;
	float		aspectratio;
	float		cam_matrix[4][4];
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_camera	camera;
	t_ambient	ambient;
	t_light		*light;
	t_obj		*objs;
	size_t		num_objs;
	t_event		event;
	int			display_info;
	t_color		bg_color;
	int			lnum;
	int			pnum;
	int			progress;
	t_bool		is_processing;
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

/* progbar.c */
void	display_progbar(t_rt *rt, int n, int max);

/* test.c */
void	init_test(t_rt *rt);

/* main.c */
int		msg_quit(char *s);

/* image.c*/
t_color	get_pixelcolor(t_img *img, float xf, float yf);
void	putpixel(t_img *img, int x, int y, int color);
void	gen_img(t_rt *rt);
void	render(t_rt *rt);
int		smart_rt(t_rt *rt, float x, float y);

/* ray.c */
void	build_camray(t_rt *rt, t_ray *ray, float x, float y);
void	build_ray(t_ray *ray, t_vect *or, t_vect *dir);
void	lookat(t_rt *rt);
// t_color	light2rgb(t_colors *l);
// t_color	light2rgb(t_obj *o, t_colors *l);

/* lightray.c */
t_color	lightrays(t_rt *rt, t_rays *r, t_light *light);
t_bool	shadow_ray(t_rt *rt, t_rays *r, t_light *light);
t_color	diffuse_light(t_rays *r, t_light *light);
t_color	specular_light(t_rays *r, t_light *light);
t_color	refraction_ray(t_rt *rt, t_rays *r, int max_reflect);
t_color	reflection_ray(t_rt *rt, t_rays *r, int max_reflect);

/* raytrace.c */
t_color	raytrace(t_rt *rt, t_rays *r, int max_reflect);
t_obj	*get_closest_obj(t_ray *ray, t_obj *obj, t_hit *hit);

/* inter.c */
int		intersect(t_ray *ray, t_obj *obj, t_hit *hit);
t_bool	cone_inter(t_ray *r, t_cone *co, t_hit *hit);
t_bool	sphere_inter(t_ray *ray, t_sphere *sp, t_hit *hit);
t_bool	plane_inter(t_ray *r, t_plane *pl, t_hit *hit);
t_bool	cylinder_inter(t_ray *r, t_cylinder *cy, t_hit *hit);
t_bool	triangle_inter(t_ray *r, t_triangle *t, t_hit *hit);

/* pattern.c */
void	set_patternref(t_rt *rt, t_obj *obj);
t_color	pattern_color(t_obj *obj, t_vect phit);
void	uv_cylco_map(t_obj *obj, t_vect p, float *uv);
void	uv_plane_map(t_obj *obj, t_vect p, float *uv);
void	uv_sphere_map(t_obj *obj, t_vect p, float *uv);

/* bumpmap.c */
void	bump_normal(t_obj *obj, t_img *img, t_hit *hit);

/* vector.c */
t_vect	vector(float x, float y, float z);
float	vectlen(t_vect v);
t_vect	vect_sub(t_vect a, t_vect b);
t_vect	vect_add(t_vect a, t_vect b);
t_vect	vect_mul(t_vect v, float f);
t_vect	*normalize(t_vect *v);
float	distance(t_vect a, t_vect b);
float	dot_prod(t_vect v1, t_vect v2);
t_vect	cross_prod(t_vect u, t_vect v);
t_vect	vect_inv(t_vect v);
t_vect	*ray_mul(t_vect *dst, t_ray *r, float t);
t_vect	reflect_vect(t_vect v, t_vect n);
t_vect	refract_vect(t_vect v, t_vect n, float eta);

/* color.c */
t_color	newcolor(float r, float g, float b);
t_color	*color_part(t_color *c, float p);
t_color	color_mul(t_color c, float p);
t_color	rgb2color(int rgb);
int		color2rgb(t_color c);
t_color	add_light(t_color color, t_color light, float p2);
t_color	mix_color(t_color c1, float p1, t_color c2, float p2);
int		big_mix(t_color	c[9]);
t_color	color_obj(t_obj *obj, t_hit *hit);

/* quadratic.c */
t_bool	solve_quadratic(t_quadratic *q);

/* object_utils.c */
void	push_object(t_obj *obj, t_obj **objs);
t_obj	*create_object(t_rt *rt, t_obj_id id);
void	free_objects(t_rt *rt, t_obj **objs);
void	object_norm(t_rt *rt);
t_vect	*get_coords(t_obj *o);

/* file.c */
int		read_file(t_rt *rt, int fd);
int		open_file(t_rt *rt, char *path);
int		is_rt_file(char *path);
int		is_invalid_file(t_rt *rt);
char	*sanitize_line(char *line);

/* number.c */
int		is_float(char *str);
int		is_ulong(char *str);

/* parsing.c */
int		parse_params(t_rt *rt, char *line);
int		parse_vector(char *str, t_vect *vect);
int		parse_color(char *str, t_color *color);
int		parse_colors(char *str, t_color *color, t_color *color2);
int		parse_float(char *str, float *num);
int		parse_ulong(char *str, size_t *num);
int		parse_resolution(t_rt *rt, char *line);
int		parse_ambient(t_rt *rt, char *line);
int		parse_camera(t_rt *rt, char *line, int i);
int		parse_light(t_rt *rt, char *line);
int		parse_plane(t_rt *rt, char **params, t_obj *obj);
int		parse_sphere(t_rt *rt, char **params, t_obj *obj);
int		parse_cylinder(t_rt *rt, char **params, t_obj *obj);
int		parse_cone(t_rt *rt, char **params, t_obj *obj);
int		parse_triangle(t_rt *rt, char **params, t_obj *obj);
int		parse_shape(t_rt *rt, char *line, t_obj_id id, int nb_params);
int		parse_extra_params(t_rt *rt, t_obj *obj, char **params, int i);
int		parse_imgpath(t_rt *rt, char *path, t_obj *obj, int type);
int		parse_specular(char *str, t_obj *obj);
int		parse_pattern(char *str, t_obj *obj);

/* array_utils.c */
void	free_array(char *arr[]);
void	print_array(char *arr[]);
int		array_length(char *arr[]);

/* ligth_utils.c */
void	push_light(t_light *new_light, t_light **lights);
t_light	*create_light(t_rt *rt);
void	free_lights(t_light **lights);

/* convert.c */
float	str_to_float(char *str);
int		str_to_int_color(char *str);

/* error.c */
int		show_parsing_error(t_rt *rt, char **params, char *msg);
int		show_error(char *msg);

/* time.c */
double   get_timediff(void);
void	multi_gen(t_rt *rt);

/* debug.c */
void	rt_dump(t_rt *rt);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:42:00 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/18 18:40:11 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1500
# define WIN_HEIGHT 1200
# define ON_KEYDOWN 2

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
# include "parsing.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_rt
{
	char		*path;
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_camera	camera;
	t_object	*objs;
	size_t		num_objs;
}	t_rt;

/* main.c */
int		msg_quit(char *s);
int		handle_keydown(int key, t_rt *rt);
int		handle_no_event(t_rt *rt);
void	hook_init(t_rt *rt);

/* window.c */
void	rt_init(t_rt *rt, char *path);
void	rt_clear(t_rt *rt);
int		close_window(t_rt *rt);

/* image.c*/
void	clear_img(t_img *img);
void	ft_putpixel(t_img *img, int x, int y, int color);

/* array_utils.c */
void	free_array(char *arr[]);
void	print_array(char *arr[]);
int		array_length(char *arr[]);

/* convert.c */
float	str_to_float(char *str);
int		color_to_int(char *color);
int		rgb_to_int(char **rgb);

/* error.c */
void show_parsing_error(char *msg, int lineno);

#endif
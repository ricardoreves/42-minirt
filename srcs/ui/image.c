/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:17 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/25 23:47:11 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_pixelcolor(t_img *img, float xf, float yf)
{
	char	*dst;
	int		x;
	int		y;

	x = ((int)((1 - xf) * img->width) + img->width / 2) % img->width;
	y = (int)((1 - yf) * img->height);
	if (0 <= x && x < img->width && 0 <= y && y < img->height)
	{
		dst = img->addr
			+ (y * img->line_length + x * (img->bits_per_pixel / 8));
		return (rgb2color(*(unsigned int *)dst));
	}
	return (newcolor(0, 0, 0));
}

void	*trd_gen(void *line_trd)
{
	float		x;
	float		y;
	char		*pix;
	t_line_trd	*ltrd;

	ltrd = (t_line_trd *) line_trd;
	y = ltrd->i;
	pix = ltrd->rt->img.addr;
	pix += ltrd->rt->img.line_length * ltrd->i;
	while (y < ltrd->rt->height)
	{
		x = -1;
		while (++x < ltrd->rt->width)
		{
			*(unsigned int *)pix = smart_rt(ltrd->rt, x, y);
			pix += ltrd->rt->img.addr_incr;
		}
		y += MAX_THREADS;
		pix += ltrd->rt->img.line_length * (MAX_THREADS - 1);
		put_screen_processing(ltrd->rt);
	}
	return (NULL);
}

void	multi_gen(t_rt *rt)
{
	int			i;
	t_line_trd	lines[MAX_THREADS];

	i = 0;
	object_norm(rt);
	while (i < MAX_THREADS)
	{
		lines[i].i = i;
		lines[i].rt = rt;
		pthread_create(&lines[i].trd, NULL, trd_gen, &lines[i]);
		i++;
	}
	i = 0;
	while (i < MAX_THREADS)
		pthread_join(lines[i++].trd, NULL);
}

int	smart_rt(t_rt *rt, float x, float y)
{
	t_rays	r;

	if (rt->img.antialiasing_on && !rt->event.mouse)
		return (anti_aliasing(rt, x, y));
	build_camray(rt, &r.prime_ray, x, y);
	if (rt->event.mouse)
		return (color2rgb(raytrace(rt, &r, 0)));
	return (color2rgb(raytrace(rt, &r, MAX_REFLECT)));
}

void	render(t_rt *rt)
{
	if (rt->is_processing)
		return ;
	rt->is_processing = TRUE;
	get_timediff();
	multi_gen(rt);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img.img, 0, 0);
	if (rt->display_info)
		put_info(rt);
	printf("\nDuration   :   %.2fs\n", get_timediff());
	fflush(stdout);
	rt->is_processing = FALSE;
}

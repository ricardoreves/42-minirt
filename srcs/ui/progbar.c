/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progbar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:30:20 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/22 04:59:32 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_progbar_empty(t_rt *rt, int x, int y)
{
	int	w;
	int	h;
	int	tmp;

	tmp = y;
	w = PROGBAR_W + x;
	h = PROGBAR_H + y;
	while (x < w)
	{
		y = tmp;
		while (y < h)
		{
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, DARKGREY);
			y++;
		}
		x++;
	}
}

void	draw_progbar_fill(t_rt *rt, int x, int y)
{
	int	h;

	h = PROGBAR_H + y;
	while (y < h)
	{
		mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, WHITE);
		y++;
	}
}

void	clear_progbar_digits(t_rt *rt, int x, int y)
{
	char	*tmp;

	tmp = ft_itoa(rt->progress);
	mlx_string_put(rt->mlx, rt->mlx_win, x, y, BLACK, tmp);
	free(tmp);
}

void	compute_progbar(t_rt *rt, t_progbar *pb)
{
	int	cx;
	int	cy;

	cx = rt->width / 2;
	cy = rt->height / 2;
	pb->bar_x = cx - (PROGBAR_W / 2);
	pb->bar_y = cy - (PROGBAR_H / 2);
	pb->text_x = cx - (PROGBAR_TEXT_W / 2);
	pb->text_y = cy + 20;
	pb->prog_x = cx - (PROGBAR_TEXT_W / 2) + 71;
	pb->prog_y = cy + 20;
	pb->perc_x = cx - (PROGBAR_TEXT_W / 2) + 84;
	pb->perc_y = cy + 20;
}

void	display_progbar(t_rt *rt, int n, int max)
{
	t_progbar	pb;

	printf("Processing: %3d%%\r", (n * 100) / max);
	fflush(stdout);
	if (rt->height < PROGBAR_W)
		return ;
	pb.prog = (n * 100) / max;
	pb.s_prog = ft_itoa(pb.prog);
	compute_progbar(rt, &pb);
	if (n < 2)
		draw_progbar_empty(rt, pb.bar_x, pb.bar_y);
	draw_progbar_fill(rt, pb.bar_x + ((PROGBAR_W * n) / max), pb.bar_y);
	mlx_string_put(rt->mlx, rt->mlx_win, pb.text_x, pb.text_y,
		WHITE, "Processing: ");
	clear_progbar_digits(rt, pb.prog_x, pb.prog_y);
	mlx_string_put(rt->mlx, rt->mlx_win, pb.prog_x, pb.prog_y,
		WHITE, pb.s_prog);
	mlx_string_put(rt->mlx, rt->mlx_win, pb.perc_x, pb.perc_y, WHITE, "%");
	if (n > max - 1)
		mlx_clear_window(rt->mlx, rt->mlx_win);
	free(pb.s_prog);
	rt->progress = pb.prog;
}

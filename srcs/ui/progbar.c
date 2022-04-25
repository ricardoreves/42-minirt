/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progbar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:30:20 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/25 17:22:32 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_progbar_box(t_rt *rt, int x, int y)
{
	int	w;
	int	h;
	int	tmp;

	x -= 20;
	y -= 20;
	tmp = y;
	w = PROGBAR_W + x;
	h = PROGBAR_H + y;
	while (x < w + 40)
	{
		y = tmp;
		while (y < h + 58)
		{
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, BLACK);
			y++;
		}
		x++;
	}
}

void	put_progbar_background(t_rt *rt, int x, int y)
{
	int	w;
	int	h;
	int	tmp;

	tmp = y;
	w = PROGBAR_W + x;
	h = PROGBAR_H + y;
	put_progbar_box(rt, x, y);
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

void	put_progbar_process(t_rt *rt, int x, int y)
{
	int	h;

	h = PROGBAR_H + y;
	while (y < h)
	{
		mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, WHITE);
		y++;
	}
}

char	*get_progbar_text(float percent)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(percent * 100);
	tmp2 = ft_strjoin("Processing: ", tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, "%");
	free(tmp2);
	return (tmp);
}

void	put_progbar_text(t_rt *rt, float perc)
{
	int	x;
	int	y;

	x = (rt->width * 0.5) - (PROGBAR_TEXT_W * 0.5);
	y = (rt->height * 0.5) + (PROGBAR_TEXT_H * 2);
	if (rt->process_text)
		mlx_string_put(rt->mlx, rt->mlx_win, x, y, BLACK, rt->process_text);
	rt->process_text = get_progbar_text(perc);
	mlx_string_put(rt->mlx, rt->mlx_win, x, y, WHITE, rt->process_text);
}

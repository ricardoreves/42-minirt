/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progbar2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:30:20 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/26 17:20:43 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_processing(t_rt *rt)
{
	if (rt->process > rt->height - 1)
	{
		if (IS_LINUX)
		{
			mlx_clear_window(rt->mlx, rt->mlx_win);
			free(rt->process_text);
		}
		rt->process = 0;
	}
}

void	put_console_processing(float perc)
{
	printf("Processing : %*.2f%%\r", 6, perc * 100);
	fflush(stdout);
}

void	put_screen_processing(t_rt *rt)
{
	float	perc;
	int		bar_x;
	int		bar_y;

	bar_x = (rt->width * 0.5) - (PROGBAR_W / 2);
	bar_y = (rt->height * 0.5) - (PROGBAR_H / 2);
	pthread_mutex_lock(&rt->process_lock);
	rt->process += 1;
	perc = (rt->process / rt->height);
	put_console_processing(perc);
	if (IS_LINUX && rt->height > 100 && rt->width > PROGBAR_W)
	{
		if (rt->process == 1)
			put_progbar_background(rt, bar_x, bar_y);
		put_progbar_process(rt, bar_x + ((PROGBAR_W * perc)), bar_y);
		put_progbar_text(rt, perc);
	}
	reset_processing(rt);
	pthread_mutex_unlock(&rt->process_lock);
}

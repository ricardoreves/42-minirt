/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:18:17 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/21 16:09:39 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	switch_var(int *var)
{
	if (*var)
		*var = 0;
	else
		*var = 1;
}

int	handle_keydown(int key, t_rt *rt)
{
	if (key == ESC_KEY)
		exit_win(rt);
	rt->event.key[key] = 1;
	if (key == I_KEY)
	{
		switch_var(&rt->display_info);
		render(rt);
	}
	if (key == A_KEY)
	{
		switch_var(&rt->img.antialiasing_on);
		render(rt);
	}
	return (0);
}

int	handle_keyup(int key, t_rt *rt)
{
	rt->event.key[key] = 0;
	return (0);
}

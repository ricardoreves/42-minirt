/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:18:17 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/04 01:28:07 by bgoncalv         ###   ########.fr       */
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
	if (key == ESCAPE_KEY)
		exit_win(rt);
	switch_var(&rt->event.key[key]);
	if (key == I_KEY)
	{
		switch_var(&rt->display_info);
		render(rt);
	}
	return (0);
}

int	handle_keyup(int key, t_rt *rt)
{
	switch_var(&rt->event.key[key]);
	return (0);
}

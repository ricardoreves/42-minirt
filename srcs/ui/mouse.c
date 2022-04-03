/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:19:31 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/03 02:48:43 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_mousedown(int button, int x, int y, t_rt *rt)
{
	(void) x;
	if (y < 0)
		return (0);
	rt->event.mouse |= (1 << button);
	return (0);
}

int	handle_mouseup(int button, int x, int y, t_rt *rt)
{
	(void) x;
	(void) y;
	rt->event.mouse &= ~(1 << button);
	printf("mouse click : %i\n", button);
	return (0);
}

int	handle_mousemove(int x, int y, t_rt *rt)
{
	int	dx;
	int	dy;

	rt->event.lastx = rt->event.x;
	rt->event.lasty = rt->event.y;
	rt->event.x = x;
	rt->event.y = y;
	dx = rt->event.x - rt->event.lastx;
	dy = rt->event.y - rt->event.lasty;
	return (0);
}

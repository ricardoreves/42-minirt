/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:19:31 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/24 07:52:17 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_obj(t_rt *rt, int x, int y)
{
	t_vect	*obj_pos;
	t_ray	select_ray;
	float	t;

	if (!rt->event.selection || rt->event.selection->id == id_triangle)
		return ;
	obj_pos = NULL;
	build_camray(rt, &select_ray, x, y);
	obj_pos = get_coords(rt->event.selection);
	t = (obj_pos->z - select_ray.or.z) / select_ray.dir.z;
	ray_mul(obj_pos, &select_ray, t);
	rt->event.torender = TRUE;
}

int	handle_mousedown(int button, int x, int y, t_rt *rt)
{
	t_ray	mouse_ray;
	t_hit	hit;

	build_camray(rt, &mouse_ray, x, y);
	if (y < 0)
		return (0);
	rt->event.mouse |= (1 << button);
	rt->event.selection = get_closest_obj(&mouse_ray, rt->objs, &hit);
	return (0);
}

int	handle_mouseup(int button, int x, int y, t_rt *rt)
{
	(void) x;
	(void) y;
	if (button != LEFT_CLICK)
		return (0);
	rt->event.mouse &= ~(1 << button);
	rt->event.selection = NULL;
	rt->img.antialiasing_on = FALSE;
	if (rt->event.torender)
		render(rt);
	rt->event.torender = FALSE;
	return (0);
}

int	handle_mousemove(int x, int y, t_rt *rt)
{
	rt->event.lastx = rt->event.x;
	rt->event.lasty = rt->event.y;
	rt->event.x = x;
	rt->event.y = y;
	if (rt->event.selection)
		move_obj(rt, x, y);
	return (0);
}

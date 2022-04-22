/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:19:31 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 23:00:15 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_obj(t_rt *rt, int x, int y)
{
	t_obj	*o;
	t_vect	*obj_pos;
	t_ray	select_ray;
	float	t;

	obj_pos = NULL;
	o = rt->event.selection;
	build_camray(rt, &select_ray, x, y);
	if (o->id == id_sphere)
		obj_pos = &o->object.sphere.coords;
	else if (o->id == id_plane)
		obj_pos = &o->object.plane.coords;
	else if (o->id == id_cylinder)
		obj_pos = &o->object.cylinder.coords;
	t = (obj_pos->z - select_ray.or.z) / select_ray.dir.z;
	ray_mul(obj_pos, &select_ray, t);
	render(rt);
}

int	handle_mousedown(int button, int x, int y, t_rt *rt)
{
	t_ray	mouse_ray;
	t_hit	hit;

	build_camray(rt, &mouse_ray, x, y);
	if (y < 0)
		return (0);
	printf("mouse %i\n", button);
	rt->event.mouse |= (1 << button);
	if (rt->event.mouse & LEFT_CLICK)
		rt->event.selection = get_closest_obj(&mouse_ray, rt->objs, &hit);
	return (0);
}

int	handle_mouseup(int button, int x, int y, t_rt *rt)
{
	int		alias;

	(void) x;
	(void) y;
	if (button != LEFT_CLICK)
		return (0);
	alias = rt->img.antialiasing_on;
	rt->event.mouse &= ~(1 << button);
	rt->event.selection = NULL;
	if (alias)
		rt->img.antialiasing_on = FALSE;
	render(rt);
	if (alias)
	{
		rt->img.antialiasing_on = TRUE;
		render(rt);
	}
	return (0);
}

int	handle_mousemove(int x, int y, t_rt *rt)
{
	rt->event.lastx = rt->event.x;
	rt->event.lasty = rt->event.y;
	rt->event.x = x;
	rt->event.y = y;
	if (rt->event.selection && !rt->event.key[S_KEY] && !rt->event.key[P_KEY]
		&& !rt->event.key[C_KEY])
		move_obj(rt, x, y);
	return (0);
}

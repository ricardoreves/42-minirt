/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:19:31 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/04 00:39:59 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object *create_plane(t_rt *rt, int x, int y)
{
	t_object	*obj;
	t_ray		camray;

	printf("add plane\n");
	obj = create_object(rt);
	obj->id = id_plane;
	build_camray(rt, &camray, x, y);
	ray_mul(&obj->object.plane.coords, &camray, 30);
	obj->object.plane.orient.x = 0.0;   // not correct should be calculaed with ray
	obj->object.plane.orient.y = 1.0;   // same here
	obj->object.plane.orient.z = 0.0;
	obj->object.plane.color.r = 0.8;
	obj->object.plane.color.g = 0.8;
	obj->object.plane.color.b = 0.8;
	render(rt);
	return (obj);
}

t_object *create_sphere(t_rt *rt, int x, int y)
{
	t_object	*obj;
	t_ray		camray;

	printf("add sp\n");
	obj = create_object(rt);
	obj->id = id_sphere;
	build_camray(rt, &camray, x, y);
	ray_mul(&obj->object.sphere.coords, &camray, 50);
	obj->object.sphere.color.r = 0;
	obj->object.sphere.color.g = 0.5;
	obj->object.sphere.color.b = 0;
	obj->object.sphere.diameter = 1.0;
	obj->object.sphere.r2 = 1.0;
	render(rt);
	return (obj);
}

int	handle_mousedown(int button, int x, int y, t_rt *rt)
{
	if (y < 0)
		return (0);
	rt->event.mouse |= (1 << button);
	if (button == LEFT_CLICK && (rt->event.key[S_KEY]))
		rt->event.selection = create_sphere(rt, x, y);
	if (button == LEFT_CLICK && (rt->event.key[P_KEY]))
		rt->event.selection = create_plane(rt, x, y);
	return (0);
}

int	handle_mouseup(int button, int x, int y, t_rt *rt)
{
	(void) x;
	(void) y;
	rt->event.mouse &= ~(1 << button);
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

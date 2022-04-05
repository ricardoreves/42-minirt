/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:19:31 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/05 02:51:10 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object *create_plane(t_rt *rt, t_ray *mouse_ray)
{
	t_object	*obj;

	printf("add plane\n");
	obj = create_object(rt);
	obj->id = id_plane;
	ray_mul(&obj->object.plane.coords, mouse_ray, 30);
	obj->object.plane.coords.y -= 10;
	printf("%f\n", obj->object.plane.coords.y);
	obj->object.plane.orient.x = 0.0;   // not correct should be calculaed with ray
	obj->object.plane.orient.y = 1.0;   // same here
	obj->object.plane.orient.z = 0.0;
	obj->object.plane.color.r = 0.8;
	obj->object.plane.color.g = 0.8;
	obj->object.plane.color.b = 0.8;
	render(rt);
	return (obj);
}

t_object *create_sphere(t_rt *rt, t_ray *mouse_ray)
{
	t_object	*obj;

	printf("add sp\n");
	obj = create_object(rt);
	obj->id = id_sphere;
	ray_mul(&obj->object.sphere.coords, mouse_ray, 50);
	obj->object.sphere.color.r = 0;
	obj->object.sphere.color.g = 0.5;
	obj->object.sphere.color.b = 0;
	obj->object.sphere.diameter = 1.0;
	obj->object.sphere.r2 = 1.0;
	render(rt);
	return (obj);
}

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
	t_ray	nHit;

	build_camray(rt, &mouse_ray, x, y);
	if (y < 0)
		return (0);
	rt->event.mouse |= (1 << button);
	if (button == LEFT_CLICK && (rt->event.key[S_KEY]))
		rt->event.selection = create_sphere(rt, &mouse_ray);
	else if (button == LEFT_CLICK && (rt->event.key[P_KEY]))
		rt->event.selection = create_plane(rt, &mouse_ray);
	else
		rt->event.selection = get_closest_obj(&mouse_ray, rt->objs, &nHit.or, &nHit.dir);
	return (0);
}

int	handle_mouseup(int button, int x, int y, t_rt *rt)
{
	(void) x;
	(void) y;
	rt->event.mouse &= ~(1 << button);
	rt->event.selection = NULL;
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
	if (rt->event.selection && !rt->event.key[S_KEY] && !rt->event.key[P_KEY]
			&& !rt->event.key[C_KEY])
		move_obj(rt, x, y);
	return (0);
}

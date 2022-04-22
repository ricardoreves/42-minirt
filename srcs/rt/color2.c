/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:25:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 03:15:20 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	add_light(t_color color, t_color light, float p2)
{
	t_color c;

	if (p2 > 1)
		p2 = 1;
	if (p2 < 0)
		p2 = 0;
	c.r = color.r * light.r * p2;
	c.g = color.g * light.g * p2;
	c.b = color.b * light.b * p2;
	if (c.r > 1)
		c.r = 1;
	if (c.g > 1)
		c.g = 1;
	if (c.b > 1)
		c.b = 1;
	if (c.r < 0)
		c.r = 0;
	if (c.g < 0)
		c.g = 0;
	if (c.b < 0)
		c.b = 0;
	return (c);
}

t_color	mix_color(t_color c1, float p1, t_color c2, float p2)
{
	t_color	dst;

	dst.r = c1.r * p1 + c2.r * p2;
	dst.g = c1.g * p1 + c2.g * p2;
	dst.b = c1.b * p1 + c2.b * p2;
	return (dst);
}

int	big_mix(t_color	c[9])
{
	t_color	r;
	int		i;

	i = 0;
	r = newcolor(0, 0, 0);
	while (i < 9)
	{
		r.r += c[i].r;
		r.g += c[i].g;
		r.b += c[i].b;
		i++;
	}
	r.r /= 9;
	r.g /= 9;
	r.b /= 9;
	return (color2rgb(r));
}

t_color	color_obj(t_obj *obj, t_hit *hit)
{
	float	uv[2];
	t_color	color;

	color = obj->color;
	if (obj->id == id_sphere && obj->has_texture)
	{
		uv_sphere_map(obj, hit->pHit, uv);
		color = get_pixelcolor(&obj->texture, uv[0], uv[1]);
	}
	else if (obj->pattern_num > 0)
		color = pattern_color(obj, hit->pHit);
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:25:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/24 07:52:02 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	newcolor(float r, float g, float b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	*color_part(t_color *c, float p)
{
	c->r *= c->r * p;
	c->g *= c->g * p;
	c->b *= c->b * p;
	return (c);
}

t_color	color_mul(t_color c, float p)
{
	c.r *= c.r * p;
	c.g *= c.g * p;
	c.b *= c.b * p;
	return (c);
}

t_color	rgb2color(int rgb)
{
	t_color	c;

	c.r = (float)((rgb >> 16) & 0xff) / 255;
	c.g = (float)((rgb >> 8) & 0xff) / 255;
	c.b = (float)(rgb & 0xff) / 255;
	return (c);
}

int	color2rgb(t_color c)
{
	int	color;

	color = (int)(c.r * 255) << 16;
	color += (int)(c.g * 255) << 8;
	color += (int)(c.b * 255);
	return (color);
}

t_color	add_light(t_color color, t_color light, float p2)
{
	t_color	c;

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
		uv_sphere_map(obj, hit->phit, uv);
		color = get_pixelcolor(&obj->texture, uv[0], uv[1]);
	}
	else if (obj->pattern_num > 0)
		color = pattern_color(obj, hit->phit);
	return (color);
}

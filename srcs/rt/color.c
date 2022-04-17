/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:25:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/17 01:29:04 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*color_part(t_color *c, float p)
{
	c->r *= c->r * p;
	c->g *= c->g * p;
	c->b *= c->b * p;
	return (c);
}

t_color	*color_obj(t_obj *obj)
{
	if (obj && obj->id == id_sphere)
		return (&obj->object.sphere.color);
	if (obj && obj->id == id_plane)
		return (&obj->object.plane.color);
	if (obj && obj->id == id_cylinder)
		return (&obj->object.cylinder.color);
	return (NULL);
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

t_color	*color_set(t_color *color, float r, float g, float b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

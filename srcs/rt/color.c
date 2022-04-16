/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:25:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/16 02:14:52 by bgoncalv         ###   ########.fr       */
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

	c.r = (float) ((rgb >> 16) & 0xff) / 255;
	c.g = (float) ((rgb >> 8) & 0xff) / 255;
	c.b = (float) (rgb & 0xff) / 255;
	return (c);
}

int	color2rgb(t_color c)
{
	int	color;

	color = (int) (c.r * 255) << 16;
	color += (int) (c.g * 255) << 8;
	color += (int) (c.b * 255);
	return (color);
}

t_color *color_set(t_color *color, float r, float g, float b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

t_color	*add_light(t_color *color, t_color *light, float p2)
{
	if (p2 > 1)
		p2 = 1;
	if (p2 < 0)
		p2 = 0;
	color->r = color->r * light->r * p2;
	color->g = color->g * light->g * p2;
	color->b = color->b * light->b * p2;
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
	if (color->r < 0)
		color->r = 0;
	if (color->g < 0)
		color->g = 0;
	if (color->b < 0)
		color->b = 0;
	return (color);
}

t_color	mix_color(t_color c1, float p1, t_color c2, float p2)
{
	t_color	dst;

	dst.r = c1.r * p1 + c2.r *p2;
	dst.g = c1.g * p1 + c2.g *p2;
	dst.b = c1.b * p1 + c2.b *p2;
	return (dst);
}

// int	mix_color(int c1, float p1, int c2, float p2)
// {
// 	int	dst;

// 	dst = (int) (((float) ((c1 >> 16) & 0xff)) * p1 + ((float) ((c2 >> 16) & 0xff) * p2));
// 	dst = dst << 16;
// 	dst += ((int) (((float) ((c1 >> 8) & 0xff)) * p1 + ((float) ((c2 >> 8) & 0xff) * p2))) << 8;
// 	dst += ((int) (((float) (c1 & 0xff)) * p1 + ((float) (c2 & 0xff) * p2)));
// 	return (dst);
// }
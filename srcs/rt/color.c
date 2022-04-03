/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:25:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/04 00:14:31 by bgoncalv         ###   ########.fr       */
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

int	color2rgb(t_color *c)
{
	int	color;

	color = (int) (c->r * 255) << 16;
	color += (int) (c->g * 255) << 8;
	color += (int) (c->b * 255);
	return (color);
}

int	blend_color(t_color *c, t_color *l)
{
	if (l->r < c->r)
		c->r = l->r;
	if (l->g < c->g)
		c->g = l->g;
	if (l->b < c->b)
		c->b = l->b;
	return (color2rgb(c));
}

t_color *color_set(t_color *color, float r, float g, float b)
{
	color->r = r;
	color->r = g;
	color->r = b;
	return (color);
}

int	clamp_color(t_color *c1, t_color *c2)
{
	int	r;
	int	g;
	int	b;

	r = (int) ((c1->r + c2->r) * 255);
	g = (int) ((c1->g + c2->g) * 255);
	b = (int) ((c1->b + c2->b) * 255);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

int	avg_color(t_color *c1, t_color *c2)
{
	int	color;

	color = ((int) ((c1->r + c2->r) * 255 * 0.5)) << 16;
	color += ((int) ((c1->g + c2->g) * 255 * 0.5)) << 8;
	color += (int) ((c1->b + c2->b) * 255 * 0.5);
	return (color);
}

// int	clamp_color(int c1, int c2)
// {
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = c1 >> 16 & 255 + c2 >> 16 & 255;
// 	g = c1 >> 8 & 255 + c2 >> 8 & 255;
// 	b = c1 & 255 + c2 & 255;
// 	if (r > 255)
// 		r = 255;
// 	if (g > 255)
// 		g = 255;
// 	if (b > 255)
// 		b = 255;
// 	return (r << 16 + g << 8 + b);
// }

// int	avg_color(int c1, int c2)
// {
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = c1 >> 16 & 255 + c2 >> 16 & 255;
// 	g = c1 >> 8 & 255 + c2 >> 8 & 255;
// 	b = c1 & 255 + c2 & 255;
// 	r /= 2;
// 	g /= 2;
// 	b /= 2;
// 	return (r << 16 + g << 8 + b);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:34:51 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/21 02:30:38 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	push_light(t_light *new_light, t_light **lights)
{
	t_light	*tmp;

	if (!(*lights))
		*lights = new_light;
	else
	{
		tmp = *lights;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_light;
	}
}

t_light	*create_light(t_rt *rt)
{
	t_light	*new_light;

	new_light = ft_calloc(sizeof(t_light), 1);
	if (!new_light)
		return (0);
	new_light->id = id_light;
	push_light(new_light, &rt->light);
	return (new_light);
}

void	free_lights(t_light **lights)
{
	t_light	*tmp;
	t_light	*light;

	light = *lights;
	while (light)
	{
		tmp = light;
		light = light->next;
		free(tmp);
	}
	*lights = 0;
}

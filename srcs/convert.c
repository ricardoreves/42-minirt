/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:35:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/18 19:50:36 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float str_to_float(char *str)
{
    float sum;
    float prec;
    float div;
    float sign;

    prec = 0.0;
    div = 1.0;
    sign = 1.0;
    if (str && str[0] == '-')
        sign *= -1.0;
    sum = (float)ft_atoi(str);
    // printf("sum: %f\n", sum);
    while (*str && *str != '.')
        str++;
    if (*str++ == '.')
    {
        while (*str >= '0' && *str <= '9')
        {
            div *= 10.0;
            // printf("%f\n", (*str - '0') / div);
            prec += (*str - '0') / div;
            str++;
        }
        // printf("prec: %f\n", prec);
        sum += prec * sign;
        // printf("res: %f\n", sum);
    }
    return (sum);
}

int color_to_int(char *str)
{
    int c;

    c = ft_atoi(str);
    if (c < 0)
        return (0);
    if (c > 255)
        return (255);
    return (c);
}

int	str_to_vector(char *str, t_vector *vect)
{
	char **tmp;

	tmp = ft_split(str, ',');
	if (array_length(tmp) != 3)
	{
		ft_putendl_fd("too few vector values", 2);
	}
	else
	{
		vect->x = str_to_float(tmp[0]);
		vect->y = str_to_float(tmp[1]);
		vect->z = str_to_float(tmp[2]);
	}
	free_array(tmp);
    return (0);
}

int	str_to_color(char *str, int *color)
{
	char **tmp;

	tmp = ft_split(str, ',');
	if (array_length(tmp) != 3)
	{
		ft_putendl_fd("too few color values", 2);
	}
	else
	{
        *color = color_to_int(tmp[0]);
        *color = (*color << 8) + color_to_int(tmp[1]);
        *color = (*color << 8) + color_to_int(tmp[2]);
	}
	free_array(tmp);
    return (0);
}
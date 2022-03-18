/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:35:01 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/18 14:35:33 by rpinto-r         ###   ########.fr       */
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
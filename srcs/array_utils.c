/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:28:55 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/18 14:28:57 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void free_array(char *arr[])
{
    int i;

    i = 0;
    if (arr)
    {
        while (arr[i])
            free(arr[i++]);
        free(arr);
    }
}

void print_array(char *arr[])
{
    int i;

    i = 0;
    while (arr && arr[i])
        printf("%s\n", arr[i++]);
}

int array_length(char *arr[])
{
    int i;

    i = 0;
    while (arr && arr[i])
        i++;
    return (i);
}
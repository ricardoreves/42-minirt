/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 02:17:29 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:23:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bubsort(int i_tab[], int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = i;
		while (j < n - i - 1)
		{
			if (i_tab[j] > i_tab[j + 1])
				ft_swap(&i_tab[j], &i_tab[j + 1]);
			j++;
		}
		i++;
	}
}

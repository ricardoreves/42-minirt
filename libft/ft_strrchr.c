/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <rpinto-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:33:25 by rpinto-r          #+#    #+#             */
/*   Updated: 2021/10/22 15:21:41 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	if (c > 127)
		return (str);
	while (*str)
		str++;
	while (str >= s)
	{
		if (*str == c)
			return (str);
		--str;
	}
	return (0);
}

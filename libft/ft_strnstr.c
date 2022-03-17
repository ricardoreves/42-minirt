/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <rpinto-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 00:59:48 by rpinto-r          #+#    #+#             */
/*   Updated: 2021/10/19 16:08:53 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[++i])
	{
		if (i < len && haystack[i] == needle[j])
		{
			j++;
			if (needle[j] == 0)
				return ((char *)haystack + i - --j);
		}
		else
		{
			i -= j;
			j = 0;
		}
	}
	return (0);
}

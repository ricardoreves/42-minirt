/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 01:36:15 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/01/31 01:41:22 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstsize;
	size_t	srcsize;

	dstsize = ft_strlen(dst);
	srcsize = ft_strlen(src);
	if (size > 0 && size > dstsize)
	{
		i = dstsize;
		j = 0;
		while (src[j] && i < size - 1)
			dst[i++] = src[j++];
		dst[i] = 0;
		return (dstsize + srcsize);
	}
	return (size + srcsize);
}

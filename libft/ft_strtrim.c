/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 03:08:50 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/01/31 01:42:04 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	isset(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*ptr;
	int		len;

	if (!s1)
		return (0);
	while (isset(*s1, (char *)set))
		s1++;
	if (!*s1)
		return (ft_strdup(""));
	str = (char *)s1;
	while (*s1)
		s1++;
	while (isset(*s1, (char *)set) || *s1 == 0)
		s1--;
	len = ++s1 - str;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ptr[len] = 0;
	while (len--)
		ptr[len] = str[len];
	return (ptr);
}

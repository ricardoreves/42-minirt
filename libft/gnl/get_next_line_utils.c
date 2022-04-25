/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:19:42 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/25 02:15:51 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_linelen(char *s)
{
	size_t	l;

	if (!s)
		return (0);
	l = 0;
	while (s[l])
		l++;
	return (l);
}

int	ft_hasline(char *s)
{
	if (!s)
		return (0);
	while (*s++)
		if (*s == '\n')
			return (1);
	return (0);
}

char	*ft_strndup(char *s, size_t n)
{
	size_t	i;
	char	*dst;
	size_t	l;

	if (n < ft_linelen(s))
		l = n;
	else
		l = ft_linelen(s);
	dst = malloc(l + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < l && s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*dst;
	char	*s;
	size_t	i;
	size_t	l;

	s = s1;
	l = ft_linelen(s1);
	if (ft_linelen(s2))
		l += ft_linelen(s2);
	dst = malloc(l + 1);
	if (!dst)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1)
			dst[i++] = *(s1++);
	if (s2)
		while (*s2)
			dst[i++] = *(s2++);
	dst[i] = 0;
	free(s);
	return (dst);
}

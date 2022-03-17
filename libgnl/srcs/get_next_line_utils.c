/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:19:42 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/17 21:46:44 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/get_next_line.h"

size_t	gnl_strlen(char *s)
{
	size_t	l;

	if (!s)
		return (0);
	l = 0;
	while (s[l])
		l++;
	return (l);
}

int	gnl_hasline(char *s)
{
	if (!s)
		return (0);
	while (*s++)
		if (*s == '\n')
			return (1);
	return (0);
}

char	*gnl_strndup(char *s, size_t n)
{
	size_t	i;
	char	*dst;
	size_t	l;

	if (n < gnl_strlen(s))
		l = n;
	else
		l = gnl_strlen(s);
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

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*dst;
	char	*s;
	size_t	i;
	size_t	l;

	s = s1;
	l = gnl_strlen(s1);
	if (gnl_strlen(s2))
		l += gnl_strlen(s2);
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

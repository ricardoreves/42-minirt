/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:21:49 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:23:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	d = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (d == NULL)
		return (NULL);
	ft_strlcpy(d, s1, ft_strlen(s1) + 1);
	ft_strlcpy(&d[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
	return (d);
}

char	*ft_strljoin(char *s1, char *s2, size_t l)
{
	char	*d;
	size_t	ls1;

	if (!s1 && s2)
		return (ft_strldup(s2, l + 1));
	if (s1 && !s2)
		return (ft_strldup(s1, l + 1));
	if (!s1 && !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	d = malloc(ls1 + l + 1);
	if (d == NULL)
		return (NULL);
	ft_strncpy(d, s1, ls1 + 1);
	ft_strncpy(&d[ls1], s2, l + 1);
	free(s1);
	return (d);
}

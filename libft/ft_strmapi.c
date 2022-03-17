/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <rpinto-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:49:06 by rpinto-r          #+#    #+#             */
/*   Updated: 2021/10/23 14:10:28 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*str;

	if (!s)
		return (0);
	if (!*s)
		return (ft_strdup(""));
	len = ft_strlen(s);
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (0);
	str[len] = 0;
	while (len--)
		str[len] = (*f)(len, s[len]);
	return (str);
}

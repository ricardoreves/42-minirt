/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:34:12 by rpinto-r          #+#    #+#             */
/*   Updated: 2021/10/19 22:49:04 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	nbrlen(long int ln)
{
	int		i;

	i = 0;
	if (ln == 0)
		return (1);
	if (ln < 0)
		i++;
	while (ln)
	{
		ln /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		neg;
	long	ln;

	neg = 0;
	ln = n;
	len = nbrlen(ln);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (ln < 0)
	{
		ln *= -1;
		neg = 1;
	}
	str[len] = 0;
	while (len--)
	{
		str[len] = (ln % 10) + '0';
		ln /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

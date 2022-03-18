/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:21:49 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:23:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_uilen(unsigned int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		l++;
		n /= 10;
	}
	return (l);
}

char	*ft_uitoa(unsigned int n)
{
	int		l;
	char	*s;

	l = ft_uilen(n);
	s = malloc(l + 1);
	if (s == NULL)
		return (NULL);
	s[l] = 0;
	if (n == 0)
		*s = '0';
	while (n)
	{
		s[--l] = '0' + n % 10;
		n /= 10;
	}
	return (s);
}

int	ft_uilen_base(unsigned int n, int base)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		l++;
		n /= base;
	}
	return (l);
}

char	*ft_uitoa_base(unsigned int n, char *base)
{
	int		l;
	char	*s;
	int		nbase;

	nbase = ft_strlen(base);
	l = ft_uilen_base(n, nbase);
	s = malloc(l + 1);
	if (s == NULL)
		return (NULL);
	s[l] = 0;
	if (n == 0)
		*s = base[0];
	while (n)
	{
		s[--l] = base[n % nbase];
		n /= nbase;
	}
	return (s);
}

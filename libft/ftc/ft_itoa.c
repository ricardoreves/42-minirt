/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:21:49 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:21:37 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ilen(int n)
{
	int	l;

	l = 0;
	if (n < 1)
		l++;
	while (n)
	{
		l++;
		n /= 10;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*s;

	l = ft_ilen(n);
	s = malloc(sizeof(char) * l + 1);
	if (s == NULL)
		return (NULL);
	s[l] = 0;
	if (n == 0)
		*s = '0';
	if (n < 0)
	{
		*s = '-';
		s[--l] = '0' + (-(long)n) % 10;
		n /= -10;
	}
	while (n)
	{
		s[--l] = '0' + n % 10;
		n /= 10;
	}
	return (s);
}

int	ft_ilen_base(int n, int base)
{
	int	l;

	l = 0;
	if (n < 1)
		l++;
	while (n)
	{
		l++;
		n /= base;
	}
	return (l);
}

char	*ft_itoa_base(int n, char *base)
{
	int		l;
	char	*s;
	int		nbase;

	nbase = ft_strlen(base);
	l = ft_ilen_base(n, nbase);
	s = malloc(sizeof(char) * l + 1);
	if (s == NULL)
		return (NULL);
	s[l] = 0;
	if (n == 0)
		*s = base[0];
	if (n < 0)
	{
		*s = '-';
		s[--l] = base[(-(long)n) % nbase];
		n /= -nbase;
	}
	while (n)
	{
		s[--l] = base[n % nbase];
		n /= nbase;
	}
	return (s);
}

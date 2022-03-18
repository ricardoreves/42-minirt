/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:33:36 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:23:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_ibase(char n, const char *base)
{
	int	i;

	i = 0;
	while (base[i] != n)
		i++;
	return (i);
}

unsigned int	ft_atoi_base(const char *str, const char *base)
{
	int	nb;
	int	lbase;

	nb = 0;
	lbase = ft_strlen(base);
	while (*str != '\0' && ft_ischarset(*str, base))
	{
		nb = ft_ibase(*str, base) + lbase * nb;
		str++;
	}
	return (nb);
}

unsigned int	ft_hextoi(const char *str)
{
	t_uint	nb;
	char	c;

	nb = 0;
	c = ft_tolower(*str++);
	while (c != '\0' && ft_ischarset(c, "0123456789abcdef"))
	{
		if ('0' <= c && c <= '9')
			nb = (c - '0') + 16 * nb;
		if ('a' <= c && c <= 'f')
			nb = (c - 'a') + 10 + 16 * nb;
		c = ft_tolower(*str++);
	}
	return (nb);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:33:36 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:23:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	is_negative;

	nb = 0;
	is_negative = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			is_negative = -is_negative;
	while (*str != '\0' && '0' <= *str && *str <= '9')
	{
		nb = *str - '0' + 10 * nb;
		str++;
	}
	return (nb * is_negative);
}

long	ft_atol(const char *str)
{
	long	nb;
	long	is_negative;

	nb = 0;
	is_negative = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			is_negative = -is_negative;
	while (*str != '\0' && '0' <= *str && *str <= '9')
	{
		nb = (long)(*str - '0') + (10 * nb);
		str++;
	}
	return (nb * is_negative);
}

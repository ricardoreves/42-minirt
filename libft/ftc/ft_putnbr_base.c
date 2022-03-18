/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 23:01:48 by bgoncalv          #+#    #+#             */
/*   Updated: 2021/11/05 01:22:32 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{	
	int	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

int	is_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
			if (base[i] == base[j++])
				return (0);
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		base_nb;
	char	nb_str[100];
	int		i;
	long	n;

	n = nbr;
	i = 0;
	base_nb = ft_strlen(base);
	if (base_nb > 1 && is_base(base))
	{
		if (n == 0)
			write(1, base, 1);
		if (n < 0)
			write(1, "-", 1);
		if (n < 0)
			n = -n;
		while (n != 0)
		{	
			nb_str[i++] = base[n % base_nb];
			n = n / base_nb;
		}
		while (i > 0)
			write(1, &nb_str[--i], 1);
	}
}

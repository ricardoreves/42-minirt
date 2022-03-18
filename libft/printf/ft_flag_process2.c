/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_process2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:43:07 by bgoncalv          #+#    #+#             */
/*   Updated: 2021/11/17 23:49:28 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_plus_process(t_fdata *fdata)
{	
	if (fdata->plus && !ft_memchr(fdata->current, '-', fdata->clen))
	{
		ft_addprefix(fdata, '+', 1);
	}
	return (fdata->clen);
}

int	ft_precision_string_process(t_fdata *fdata)
{
	if (fdata->dot && fdata->precision < fdata->clen)
	{
		fdata->current[fdata->precision] = 0;
		fdata->clen = fdata->precision;
	}
	return (fdata->clen);
}

int	ft_precision_number_process(t_fdata *fdata)
{
	char	*neg_sign;

	if (fdata->precision > fdata->clen - fdata->neg)
	{
		if (ft_addprefix(fdata, '0', fdata->precision - fdata->clen) == -1)
			return (-1);
		if (fdata->type == 'd' || fdata->type == 'i')
		{
			neg_sign = ft_memchr(fdata->current, '-', fdata->clen);
			if (neg_sign)
			{
				*neg_sign = '0';
				if (ft_addprefix(fdata, '-', 1) == -1)
					return (-1);
			}
		}
	}
	else if (fdata->dot && fdata->precision == 0
		&& fdata->current[0] == '0' && fdata->current[1] == 0)
	{
		free(fdata->current);
		fdata->current = ft_strdup("");
		fdata->clen = 0;
	}
	return (fdata->clen);
}

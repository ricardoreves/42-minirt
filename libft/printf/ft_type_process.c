/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:45:56 by bgoncalv          #+#    #+#             */
/*   Updated: 2021/11/17 23:49:00 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_process(t_fdata *fdata)
{
	int	i;

	i = va_arg(fdata->ap, int);
	fdata->current = ft_itoa(i);
	if (fdata->current == NULL)
		return (-1);
	fdata->clen = ft_strlen(fdata->current);
	if (fdata->current[0] == '-')
		fdata->neg = 1;
	ft_precision_number_process(fdata);
	ft_plus_process(fdata);
	ft_space_process(fdata);
	ft_width_process(fdata);
	if (fdata->zero)
		ft_fix_plusminus(fdata);
	return (fdata->clen);
}

int	ft_uint_process(t_fdata *fdata)
{
	unsigned int	i;

	i = va_arg(fdata->ap, unsigned int);
	fdata->current = ft_uitoa(i);
	if (fdata->current == NULL)
		return (-1);
	fdata->clen = ft_strlen(fdata->current);
	ft_precision_number_process(fdata);
	ft_plus_process(fdata);
	ft_width_process(fdata);
	return (fdata->clen);
}

int	ft_ulong_process(t_fdata *fdata)
{
	unsigned long	ul;

	ul = va_arg(fdata->ap, unsigned long);
	fdata->current = ft_ultoa_base(ul, "0123456789abcdef");
	if (fdata->current == NULL)
		return (-1);
	fdata->clen = ft_strlen(fdata->current);
	ft_hash_process(fdata);
	ft_width_process(fdata);
	return (fdata->clen);
}

int	ft_hex_process(t_fdata *fdata)
{
	unsigned int	i;

	i = va_arg(fdata->ap, unsigned int);
	if (fdata->type == 'X')
		fdata->current = ft_uitoa_base(i, "0123456789ABCDEF");
	else
		fdata->current = ft_uitoa_base(i, "0123456789abcdef");
	if (fdata->current == NULL)
		return (-1);
	fdata->clen = ft_strlen(fdata->current);
	ft_precision_number_process(fdata);
	ft_hash_process(fdata);
	ft_width_process(fdata);
	return (fdata->clen);
}

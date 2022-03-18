/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_process2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:45:56 by bgoncalv          #+#    #+#             */
/*   Updated: 2021/12/05 01:33:31 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char_process(t_fdata *fdata)
{
	char	c;

	c = va_arg(fdata->ap, int);
	fdata->current = malloc(2);
	if (fdata->current == NULL)
		return (-1);
	fdata->current[0] = c;
	fdata->current[1] = 0;
	fdata->clen = 1;
	ft_space_process(fdata);
	ft_width_process(fdata);
	return (fdata->clen);
}

int	ft_percent_process(t_fdata *fdata)
{
	fdata->current = malloc(2);
	if (fdata->current == NULL)
		return (-1);
	fdata->current[0] = '%';
	fdata->current[1] = 0;
	fdata->clen = 1;
	ft_width_process(fdata);
	return (fdata->clen);
}

int	ft_string_process(t_fdata *fdata)
{
	char	*s;

	s = va_arg(fdata->ap, char *);
	if (s)
		fdata->current = ft_strdup(s);
	else
		fdata->current = ft_strdup("(null)");
	fdata->clen = ft_strlen(fdata->current);
	ft_precision_string_process(fdata);
	ft_width_process(fdata);
	return (fdata->clen);
}

int	ft_float_process(t_fdata *fdata)
{
	double	d;
	char	*tmp;
	char	dec_part[5];
	int		i;

	d = va_arg(fdata->ap, double);
	tmp = ft_itoa((int) d);
	fdata->current = ft_strjoin(tmp, ".");
	free(tmp);
	d -= (double)(int)d;
	i = 0;
	while (i < 4)
	{
		d = d * 10.0;
		dec_part[i++] = '0' + ((int) d) % 10;
	}
	dec_part[4] = 0;
	tmp = ft_strjoin(fdata->current, dec_part);
	free(fdata->current);
	fdata->current = tmp;
	fdata->clen = ft_strlen(fdata->current);
	return (fdata->clen);
}

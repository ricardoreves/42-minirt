/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:00:55 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/17 19:50:42 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/get_next_line.h"

 int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

 char	*gnl_strdup(char *s)
{
	char	*str;
	int		len;

	len = gnl_strlen(s);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	str[len] = 0;
	while (len--)
		str[len] = s[len];
	return (str);
}

 char	*gnl_concat_buffer(char *buffer, char *buffer_read)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	len = gnl_strlen(buffer) + gnl_strlen(buffer_read);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (buffer[j])
		str[i++] = buffer[j++];
	j = 0;
	while (buffer_read[j])
		str[i++] = buffer_read[j++];
	str[i] = 0;
	gnl_free(buffer);
	return (str);
}

 void	gnl_update_buffer(char **buffer, int start)
{
	int		i;
	int		len;
	char	*tmp;

	tmp = *buffer;
	len = gnl_strlen(tmp) - start;
	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
		gnl_free(tmp);
	else
	{
		i = 0;
		while (i < len)
			tmp[i++] = (*buffer)[start++];
		tmp[i] = 0;
	}
	gnl_free(*buffer);
	*buffer = tmp;
}

 char	*gnl_free(char *str)
{
	if (str)
	{
		free(str);
		str = 0;
	}
	return (str);
}

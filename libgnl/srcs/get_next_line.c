/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:07:21 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/17 19:48:55 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/get_next_line.h"

 int	gnl_has_next_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (i);
	return (0);
}

 int	gnl_length_next_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (i);
	return (i);
}

 char	*gnl_return_next_line(char **buffer)
{
	int		i;
	int		len;
	char	*line;

	len = gnl_length_next_line(*buffer);
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (0);
	i = -1;
	while (++i < len)
		line[i] = (*buffer)[i];
	line[len] = 0;
	gnl_update_buffer(buffer, len);
	return (line);
}

char	*get_next_line(int fd)
{
	 char	*buffer;
	 char	buffer_read[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	while (1)
	{
		bytes_read = read(fd, buffer_read, BUFFER_SIZE);
		if (bytes_read < 0 || (bytes_read == 0 && buffer_read[0] == 0))
			return (0);
		if (!buffer)
			buffer = gnl_strdup("");
		if ((bytes_read == 0 && buffer[0] == 0))
			return (gnl_free(buffer));
		if (bytes_read == 0)
			break ;
		buffer_read[bytes_read] = 0;
		buffer = gnl_concat_buffer(buffer, buffer_read);
		if (gnl_has_next_line(buffer))
			break ;
	}
	return (gnl_return_next_line(&buffer));
}

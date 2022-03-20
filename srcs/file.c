/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:36:59 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/20 06:31:28 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	 check_file_extension(char *path)
{
	int len;

	len = ft_strlen(path) - 3;
	if (len > 3)
		return (ft_strncmp(path + len, ".rt", 3) == 0);
	return (0);
}

int read_file(t_rt *rt, int fd)
{
	int num;
	int ret;
	char *line;

	num = 0;
	ret = 0;
	while (ret != 1)
	{
		num++;
		line = get_next_line(fd);
		if (!line)
			break;
		line = sanitize_line(line);
		if (parse_line(rt, line, num))
			ret = 1;
		free(line);
	}
	close(fd);
	return (ret);
}

int open_file(t_rt *rt, char *path)
{
	int fd;

	if (!check_file_extension(path))
	{
		ft_putendl_fd("Error: invalid file extension", 2);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (0);
	}
	if (read_file(rt, fd))
		return (0);
	return (1);
}
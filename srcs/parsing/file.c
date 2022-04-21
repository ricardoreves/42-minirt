/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:36:59 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/21 16:00:43 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_invalid_file(t_rt *rt)
{
	if (!rt->ambient.id)
		return (show_error(ERR_MISSING_AMBIENT_PARAMS));
	if (!rt->camera.id)
		return (show_error(ERR_MISSING_CAMERA_PARAMS));
	if (!rt->light)
		return (show_error(ERR_MISSING_LIGHT_PARAMS));
	return (0);
}

int	is_rt_file(char *path)
{
	int	len;

	len = ft_strlen(path) - 3;
	if (len > 3)
		return (ft_strncmp(path + len, ".rt", 3) == 0);
	return (0);
}

int	read_file(t_rt *rt, int fd)
{
	int		num;
	int		ret;
	char	*line;

	num = 0;
	ret = 0;
	while (ret != 1)
	{
		num++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line = sanitize_line(line);
		rt->lnum = num;
		if (parse_params(rt, line))
			ret = 1;
		free(line);
	}
	if (!ret && is_invalid_file(rt))
		ret = 1;
	close(fd);
	return (ret);
}

int	open_file(t_rt *rt, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (!show_error(ERR_FILE_NOT_FOUND));
	if (!is_rt_file(path))
		return (!show_error(ERR_IS_NOT_RT_FILE));
	if (read_file(rt, fd))
		return (0);
	return (1);
}

char	*sanitize_line(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	free(tmp);
	return (line);
}

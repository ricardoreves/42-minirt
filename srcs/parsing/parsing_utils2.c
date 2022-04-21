/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 02:53:40 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/04/21 16:55:34 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_imgpath(t_rt *rt, char *path, t_img *img)
{
	int		fd;
	t_img	im;
	void	*mlx_ptr;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	mlx_ptr = mlx_init();
	im.img = mlx_xpm_file_to_image(mlx_ptr, path, &im.width, &im.height);
	if (!im.img)
		return (1);
	im.addr = mlx_get_data_addr(im.img, &im.bits_per_pixel, &im.line_length, &im.endian);
	img = &im;
	return (0);
}

int	parse_specular(char *str, t_obj *obj)
{
	int		i;
	int		ret;
	char	**params;

	i = -1;
	ret = 0;
	params = ft_split(str, ',');
	while (params && params[++i])
		if (!is_float(params[i]))
			ret = 1;
	if (array_length(params) != 2)
		ret = 1;
	else
	{
		obj->speckv = str_to_float(params[0]);
		obj->specn = str_to_float(params[1]);
	}
	free_array(params);
	return (ret);
}

int	parse_pattern(char *str, t_obj *obj)
{
	int		i;
	int		ret;
	char	**params;

	i = -1;
	ret = 0;
	params = ft_split(str, ',');
	if (array_length(params) != 2)
		ret = 1;
	if (!is_float(params[0]))
		ret = 1;
	if (!is_ulong(params[1]))
		ret = 1;
	if (!ret)
	{
		obj->pattern_len = str_to_float(params[0]);
		obj->pattern_num = ft_atoi(params[1]);
	}
	free_array(params);
	return (ret);
}

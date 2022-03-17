/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 19:53:04 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/01/31 01:41:06 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	compute_tab_size(char *s, char c)
{
	int	i;

	i = 0;
	if (!c)
		return (1);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == 0)
			return (0);
		while (*s != c && *s != 0)
			s++;
		while (*s == c)
			s++;
		i++;
	}
	return (i);
}

static	int	malloc_tab_entry(char **tab, char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	if (!c)
		return (1);
	while (*s)
	{
		while (*s == c)
			s++;
		j = 0;
		while (*s != c && *s != 0)
		{
			j++;
			s++;
		}
		tab[i] = malloc(sizeof(char) * (j + 1));
		if (!tab[i])
			return (0);
		while (*s == c)
			s++;
		i++;
	}
	return (1);
}

static	char	**copy_tab_entry(char **tab, char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	if (!c)
	{
		tab[0] = malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (!tab[0])
			return (0);
		ft_strlcpy(tab[0], s, (ft_strlen(s) + 1));
	}
	while (c && *s)
	{
		while (*s == c)
			s++;
		j = 0;
		while (*s != c && *s != 0)
			tab[i][j++] = *s++;
		tab[i][j] = 0;
		while (*s == c)
			s++;
		i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		tab_size;

	tab_size = compute_tab_size((char *)s, c);
	tab = malloc(sizeof(char *) * (tab_size + 1));
	if (!tab)
		return (0);
	else if (!tab_size || !*s)
		tab[0] = 0;
	else if (malloc_tab_entry(tab, (char *)s, c))
		copy_tab_entry(tab, (char *)s, c);
	else
	{
		free(tab);
		return (0);
	}
	tab[tab_size] = 0;
	return (tab);
}

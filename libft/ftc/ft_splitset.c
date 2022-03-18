/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:43:52 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:23:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	next_charset(char *str, char *charset)
{	
	int	i;

	i = 0;
	while (str[i] && !ft_ischarset(str[i], charset))
		i++;
	if (!str[i])
		return (i + 1);
	return (i);
}

static char	*ft_substrs(char *str, int n)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_count_wordset(char *str, char *charset)
{
	int	nb_words;
	int	pre_char;
	int	i;

	nb_words = 0;
	pre_char = -1;
	i = 0;
	while (str[i])
	{
		if (ft_ischarset(str[i], charset))
		{	
			if (i - pre_char > 1)
				nb_words++;
			pre_char = i;
		}
		i++;
	}
	if (i - pre_char > 1)
		nb_words++;
	return (nb_words);
}

char	**ft_splitset(char *str, char *charset)
{
	char	**dest;
	int		i;
	int		end;

	dest = malloc(sizeof(char *) * (ft_count_wordset(str, charset) + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (*str)
	{	
		end = next_charset(str, charset);
		if (end > 0)
		{
			dest[i] = ft_substrs(str, end);
			i++;
			str += end - 1;
		}
		str++;
	}
	dest[i] = 0;
	return (dest);
}

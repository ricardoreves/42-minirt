/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:19:44 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/03/17 21:45:55 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h> 
# include <stdlib.h>

size_t	gnl_strlen(char *s);
int		gnl_hasline(char *s);
char	*gnl_strndup(char *s, size_t l);
char	*gnl_strjoin(char *s1, char *s2);

char	*get_next_line(int fd);

#endif

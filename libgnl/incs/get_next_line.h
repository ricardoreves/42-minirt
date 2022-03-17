/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:03:28 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/17 19:49:45 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*gnl_return_next_line(char **buffer);
int		gnl_has_next_line(char *s);
int		gnl_length_next_line(char *s);
int		gnl_strlen(char *s);
char	*gnl_strdup(char *s);
char	*gnl_free(char *str);
char	*gnl_concat_buffer(char *buffer, char *buffer_read);
void	gnl_update_buffer(char **buffer, int start);

#endif
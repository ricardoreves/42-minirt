/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:19:40 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 17:23:44 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

typedef struct s_list	t_list;

typedef struct s_list
{
	int		fd;
	char	*s_left;
	t_list	*prev;
	t_list	*next;
}	t_list;

static t_list	*list_init(int fd)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->fd = fd;
	lst->s_left = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

static t_list	*lfd_process(t_list *lst, int fd)
{
	if (!lst)
		return (list_init(fd));
	while (lst->next)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	if (lst->fd == fd)
		return (lst);
	lst->next = list_init(fd);
	lst->next->prev = lst;
	return (lst->next);
}

static void	clear_node(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp->prev)
	{
		if (tmp->s_left)
			free(tmp->s_left);
		if (tmp->next)
			tmp->next->prev = NULL;
		*lst = tmp->next;
	}
	else
	{
		if (tmp->s_left)
			free(tmp->s_left);
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		while ((*lst)->prev)
			*lst = (*lst)->prev;
	}
	free(tmp);
}

static char	*get_line(t_list **lst)
{
	size_t	l;
	char	*dst;
	char	*tmp;

	l = 0;
	if (!(*lst)->s_left)
	{
		clear_node(lst);
		return (NULL);
	}
	while ((*lst)->s_left[l] && (*lst)->s_left[l] != '\n')
		l++;
	if ((*lst)->s_left[l] == '\n')
		l++;
	if (!(*lst)->s_left[l])
		tmp = NULL;
	else
		tmp = ft_strndup((*lst)->s_left + l, ft_strlen((*lst)->s_left + l));
	dst = ft_strndup((*lst)->s_left, l);
	free((*lst)->s_left);
	(*lst)->s_left = tmp;
	if (!(*lst)->s_left)
		clear_node(lst);
	return (dst);
}

char	*get_next_line(int fd)
{
	static t_list	*lfd = NULL;
	char			buffer[BUFFER_SIZE + 1];
	size_t			n;

	if (fd < 0 || 4095 < fd || BUFFER_SIZE < 0)
		return (NULL);
	lfd = lfd_process(lfd, fd);
	if (lfd->s_left && ft_hasline(lfd->s_left))
		return (get_line(&lfd));
	n = read(fd, buffer, BUFFER_SIZE);
	buffer[n] = 0;
	while (0 < n && n <= BUFFER_SIZE)
	{
		lfd->s_left = ft_strjoin(lfd->s_left, buffer);
		if (!lfd->s_left || ft_hasline(lfd->s_left))
			break ;
		n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = 0;
	}
	return (get_line(&lfd));
}

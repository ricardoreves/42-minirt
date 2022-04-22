/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:54:02 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/22 16:11:05 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlnew(void)
{
	t_dlist	*dl;

	dl = malloc(sizeof(t_dlist));
	if (!dl)
		return (dl);
	dl->length = 0;
	dl->first = NULL;
	dl->last = NULL;
	return (dl);
}

void	ft_dlinit(t_dlist *dl)
{
	dl->length = 0;
	dl->first = NULL;
	dl->last = NULL;
}

void	ft_dlclear(t_dlist **dl, void (*f)(void *))
{
	t_node	*current;
	t_node	*next;

	if (!*dl)
		return ;
	current = (*dl)->first;
	while (current)
	{
		next = current->next;
		f(current->content);
		free(current);
		current = next;
	}
	free(*dl);
	*dl = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:07:57 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/30 18:09:03 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dladdfirst(t_dlist *dl, void *content)
{
	t_node	*node;

	if (!dl)
		dl = ft_dlnew();
	node = malloc(sizeof(t_node));
	if (!node)
		return (dl);
	node->prev = NULL;
	node->next = dl->first;
	node->content = content;
	if (dl->first)
	{
		dl->first->prev = node;
		dl->first = node;
	}
	else
	{
		dl->first = node;
		dl->last = node;
	}
	if (node)
		dl->length++;
	return (dl);
}

t_dlist	*ft_dladdlast(t_dlist *dl, void *content)
{
	t_node	*node;

	if (!dl)
		dl = ft_dlnew();
	node = malloc(sizeof(t_node));
	if (!node || !dl)
		return (dl);
	node->prev = dl->last;
	node->next = NULL;
	node->content = content;
	if (dl->last)
	{
		dl->last->next = node;
		dl->last = node;
	}
	else
	{
		dl->first = node;
		dl->last = node;
	}
	if (node)
		dl->length++;
	return (dl);
}

void	*ft_dlgetcontent(t_dlist *dl, size_t i)
{
	t_node	*node;

	if (!dl || i > dl->length)
		return (NULL);
	node = dl->first;
	while (i--)
		node = node->next;
	return (node->content);
}

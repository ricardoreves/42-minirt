/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 00:42:41 by rpinto-r          #+#    #+#             */
/*   Updated: 2021/12/07 16:29:01 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*item;

	if (!lst)
		return (0);
	newlst = 0;
	while (lst)
	{
		item = ft_lstnew((*f)(lst->content));
		if (!item)
			ft_lstclear(&item, (*del));
		else
			ft_lstadd_back(&newlst, item);
		lst = lst->next;
	}
	return (newlst);
}

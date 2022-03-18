/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:27:48 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:20:47 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlisordered(t_dlist *dl, int (*f)(t_node *, t_node *))
{
	t_node	*current;

	if (!dl || dl->length == 0)
		return (0);
	if (dl->length == 1)
		return (1);
	current = dl->first;
	while (current->next)
	{
		if (f(current, current->next))
			return (0);
		current = current->next;
	}
	return (1);
}

static void	ft_printilist(t_dlist *dl, int rev)
{
	t_node	*current;

	ft_printf("Length of lst : %i \n", (int) dl->length);
	if (dl->length)
	{
		ft_printf("First node content : %i\n", *(int *)dl->first->content);
		ft_printf("Last node content  : %i\n", *(int *)dl->last->content);
		ft_printf("lst         : ");
	}
	current = dl->first;
	while (current)
	{
		ft_printf("%i ", *(int *)current->content);
		current = current->next;
	}
	if (dl->length && rev)
		ft_printf("\nreverse lst : ");
	current = dl->last;
	while (current && rev)
	{
		ft_printf("%i ", *(int *)current->content);
		current = current->prev;
	}
}

void	ft_printdlsti(t_dlist *dl, int rev, int (*f)(t_node *, t_node *))
{
	if (!dl)
	{
		ft_printf("lst Empty\n");
		return ;
	}
	ft_printilist(dl, rev);
	ft_printf("\n");
	ft_printf("is ordered : %i\n", ft_dlisordered(dl, f));
}

t_dlist	*ft_dlcpy(t_dlist *dl, void *(*f)(void *))
{
	t_dlist	*dldst;
	t_node	*node;

	if (!dl || !f)
		return (NULL);
	dldst = ft_dlnew();
	if (!dldst)
		return (NULL);
	if (!dl->length)
		return (dldst);
	node = dl->first;
	while (node)
	{
		ft_dladdlast(dldst, f(node->content));
		node = node->next;
	}
	return (dldst);
}

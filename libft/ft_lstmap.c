/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:16:53 by aandric           #+#    #+#             */
/*   Updated: 2021/11/16 18:26:35 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	head = NULL;
	while (lst)
	{
		node = ft_lstnew((f)(lst -> content));
		if (!node)
		{
			ft_lstclear(&head, (del));
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		lst = lst -> next;
	}
	return (head);
}

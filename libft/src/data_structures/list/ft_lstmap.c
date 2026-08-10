/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:33:18 by Camille           #+#    #+#             */
/*   Updated: 2025/11/03 15:38:36 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

static int	fill_map(t_list *tail, t_list *lst,
						void *(*f)(void *), void (*del)(void *))
{
	void	*content;

	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (0);
		tail->next = ft_lstnew(content);
		if (!tail->next)
		{
			del(content);
			return (0);
		}
		tail = tail->next;
		lst = lst->next;
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	content = f(lst->content);
	if (!content)
		return (NULL);
	head = ft_lstnew(content);
	if (!head)
	{
		del(content);
		return (NULL);
	}
	if (!fill_map(head, lst->next, f, del))
	{
		ft_lstclear(&head, del);
		return (NULL);
	}
	return (head);
}

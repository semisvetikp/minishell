/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:40:45 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/11 14:14:48 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *elem;
	t_list *new;

	if (!lst || !f)
		return (NULL);
	elem = ft_lstnew(f(lst->content));
	new = elem;
	while (lst->next)
	{
		lst = lst->next;
		if (!(elem->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&elem, del);
			return (NULL);
		}
		elem = elem->next;
	}
	return (new);
}

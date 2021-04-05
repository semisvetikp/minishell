/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:05:49 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/10 15:59:31 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *elem;

	if (!(lst && *lst && del))
		return ;
	while (lst && *lst)
	{
		elem = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		(*lst) = elem;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:55:26 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/09 23:23:25 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *elem;

	if (lst == NULL)
		return (NULL);
	elem = lst;
	while (elem->next != NULL)
	{
		elem = elem->next;
	}
	return (elem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:18:26 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/09 23:39:05 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = (t_list*)malloc(sizeof(t_list));
	if (elem != NULL)
	{
		elem->next = NULL;
		elem->content = content;
	}
	return (elem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:59:39 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/05 14:32:22 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char *k;

	k = (void*)malloc(count * size);
	if (k == NULL)
		return (NULL);
	ft_bzero(k, count * size);
	*k = '\0';
	return (k);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:31:45 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/05 15:03:43 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	size_t			k;

	k = 0;
	s = (unsigned char*)b;
	while (len > 0)
	{
		s[k] = (unsigned char)c;
		k++;
		len--;
	}
	return (b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:44:08 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/09 22:07:20 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buf;
	size_t			k;

	k = 0;
	buf = (unsigned char *)s;
	while (k < n)
	{
		if (buf[k] == (unsigned char)c)
			return (&buf[k]);
		k++;
	}
	return (NULL);
}

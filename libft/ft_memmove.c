/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:05:21 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/05 16:18:28 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*d;
	unsigned const char *s;
	size_t				kk;

	kk = 0;
	d = (unsigned char*)dest;
	s = (unsigned const char*)src;
	if (src == dest)
		return (dest);
	if (s < d)
		while (len--)
		{
			d[len] = s[len];
		}
	else
		while (len > 0)
		{
			d[kk] = s[kk];
			kk++;
			len--;
		}
	return (dest);
}

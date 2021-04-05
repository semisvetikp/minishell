/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:31:45 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/06 20:21:15 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	*resource;
	int				k;

	k = 0;
	s = (unsigned char*)dst;
	resource = (unsigned char*)src;
	while (n > 0)
	{
		s[k] = resource[k];
		if (s[k] == (unsigned char)c)
			return (&dst[k + 1]);
		k++;
		n--;
	}
	return (NULL);
}

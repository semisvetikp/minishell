/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:31:45 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/05 16:18:53 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s;
	const char		*resource;
	int				k;

	k = 0;
	s = (unsigned char*)dst;
	resource = (const char*)src;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (n > 0)
	{
		s[k] = resource[k];
		k++;
		n--;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:37:31 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/05 16:18:03 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*b1;
	const unsigned char	*b2;
	int					diff;

	b1 = (unsigned char*)s1;
	b2 = (unsigned char*)s2;
	while (n > 0)
	{
		diff = *b1 - *b2;
		if (diff != 0)
			return (diff);
		b1++;
		b2++;
		n--;
	}
	return (0);
}

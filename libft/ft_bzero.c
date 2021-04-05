/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 22:35:42 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/05 14:31:22 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*b;
	size_t			k;
	size_t			c;

	c = 0;
	k = 0;
	b = (unsigned char*)s;
	while (n > 0)
	{
		b[k] = (unsigned char)c;
		k++;
		n--;
	}
}

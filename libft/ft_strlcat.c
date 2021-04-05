/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:07:37 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/11 15:06:11 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	kk;
	size_t	len;
	size_t	ld;

	kk = 0;
	ld = ft_strlen(dst);
	len = ft_strlen(src);
	if (dstsize <= ld)
		return (len + dstsize);
	else
		len = len + ld;
	while (src[kk] && ld < dstsize - 1)
	{
		dst[ld] = src[kk];
		ld++;
		kk++;
	}
	dst[ld] = '\0';
	return (len);
}

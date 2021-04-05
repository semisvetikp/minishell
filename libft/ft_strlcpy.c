/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:26:23 by jradioac          #+#    #+#             */
/*   Updated: 2021/03/31 16:53:17 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	k;

	k = 0;
	if (dst == NULL && src == NULL)
		return (0);
	if (dstsize > 0)
	{
		while (src[k] && k < dstsize - 1)
		{
			dst[k] = src[k];
			k++;
		}
		dst[k] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strlcpy2(char *dst, const char *src, size_t dstsize)
{
	size_t k;

	k = 0;
	if (dst == NULL && src == NULL)
		return (0);
	if (dstsize > 0)
	{
		while (src[k] && k < dstsize - 1)
		{
			dst[k] = src[k];
			k++;
		}
		dst[k] = '\0';
	}
	return (dst);
}

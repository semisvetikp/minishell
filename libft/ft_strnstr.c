/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:14:55 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/06 16:12:55 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t	k;
	size_t	kk;
	int		j;
	int		bb;

	k = 0;
	kk = 0;
	while (l[k])
		k++;
	bb = ft_strlen(b);
	if (k == 0)
		return ((char*)b);
	while (kk < len && len - kk >= k)
	{
		if (b[kk] == l[0])
		{
			j = ft_strncmp(&b[kk], l, k);
			if (j == 0)
				return ((char *)b + kk);
		}
		kk++;
	}
	return (NULL);
}

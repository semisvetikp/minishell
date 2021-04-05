/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:22:42 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/07 00:28:09 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	k;
	size_t	l;
	char	*str;

	k = 0;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	if (str == NULL)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l)
	{
		str[k] = '\0';
		return (str);
	}
	while (k < len)
	{
		str[k] = s[start + k];
		k++;
	}
	str[k] = '\0';
	return (str);
}

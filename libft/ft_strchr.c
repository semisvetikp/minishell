/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:29:21 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/05 16:08:04 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		k;

	k = 0;
	str = (char *)s;
	while (str[k] != (char)c)
	{
		if (str[k] == '\0')
			return (0);
		k++;
	}
	return (&str[k]);
}

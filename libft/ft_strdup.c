/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:40:25 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/02 01:34:34 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		k;
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	k = ft_strlen(s1) + 1;
	s2 = (char*)malloc(sizeof(char) * k);
	if (s2 == NULL)
		return (NULL);
	ft_memcpy(s2, s1, k);
	return (s2);
}

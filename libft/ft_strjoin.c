/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:06:21 by jradioac          #+#    #+#             */
/*   Updated: 2021/03/31 17:10:44 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	k;
	size_t	kk;

	k = 0;
	kk = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[k])
	{
		str[k] = s1[k];
		k++;
	}
	while (s2[kk])
	{
		str[k] = s2[kk];
		k++;
		kk++;
	}
	str[k] = '\0';
	return (str);
}

char		*ft_strjoin2(char *s1, char const *s2)
{
	char	*str;
	size_t	k;
	size_t	kk;

	k = 0;
	kk = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[k])
	{
		str[k] = s1[k];
		k++;
	}
	while (s2[kk])
	{
		str[k] = s2[kk];
		k++;
		kk++;
	}
	str[k] = '\0';
	free(s1);
	return (str);
}

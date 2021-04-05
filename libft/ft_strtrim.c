/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:26:15 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/07 19:46:56 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	n;
	size_t	k;
	size_t	l;

	n = 0;
	k = 0;
	if (!s1)
		return (NULL);
	l = ft_strlen(s1);
	while (s1[n] && ft_strchr(set, s1[n]))
		n++;
	if (n == l)
		return (ft_substr("", 0, 1));
	while (ft_strrchr(set, s1[l - k - 1]))
		k++;
	return (ft_substr(s1, n, l - k - n));
}

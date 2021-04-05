/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 13:46:34 by jradioac          #+#    #+#             */
/*   Updated: 2021/02/21 01:19:34 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		sum_word(char const *str, char del)
{
	int	k;
	int	kol;

	k = 0;
	kol = 0;
	while (str[k] != '\0')
	{
		while (str[k] == del && str[k] != '\0')
			k++;
		if (str[k] != del && str[k] != '\0')
		{
			kol++;
			while (str[k] != del && str[k] != '\0')
				k++;
		}
	}
	return (kol);
}

static char		*ft_word(char const *str, char del)
{
	char	*w;
	int		k;

	k = 0;
	while (str[k] && str[k] != del)
		k++;
	w = (char*)malloc(sizeof(char) * (k + 1));
	if (w == NULL)
		return (NULL);
	k = 0;
	while (str[k] && str[k] != del)
	{
		w[k] = str[k];
		k++;
	}
	w[k] = '\0';
	return (w);
}

char			**ft_split(char const *s, char c)
{
	char	**str;
	int		k;
	int		i;

	k = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char**)malloc(sizeof(char*) * (sum_word(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (s[k])
	{
		while (s[k] == c && s[k] != '\0')
			k++;
		if (s[k] != c && s[k] != '\0')
			str[i++] = ft_word(&s[k], c);
		while (s[k] != c && s[k] != '\0')
			k++;
	}
	str[i] = NULL;
	return (str);
}

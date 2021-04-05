/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:44:16 by jradioac          #+#    #+#             */
/*   Updated: 2021/03/10 18:46:41 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	k;

	k = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[k] == s2[k] && s1[k] != '\0')
	{
		if (s1[k] != s2[k])
		{
			return (s1[k] - s2[k]);
			break ;
		}
		k++;
	}
	return ((unsigned char)s1[k] - (unsigned char)s2[k]);
}

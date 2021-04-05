/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 22:06:50 by jradioac          #+#    #+#             */
/*   Updated: 2020/11/12 01:00:12 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intl(int n)
{
	int	k;

	k = 0;
	if (n <= 0)
	{
		n = -n;
		k++;
	}
	while (n)
	{
		k++;
		n = n / 10;
	}
	return (k);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		l;
	int		m;

	m = n;
	l = ft_intl(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s = (char*)malloc(sizeof(char) * (l + 1));
	if (s == NULL)
		return (NULL);
	if (n < 0)
		m = -m;
	while (l)
	{
		l--;
		s[l] = m % 10 + '0';
		m = m / 10;
	}
	if (n < 0)
		s[0] = '-';
	s[ft_intl(n)] = '\0';
	return (s);
}

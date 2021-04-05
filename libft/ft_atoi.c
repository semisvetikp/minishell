/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:26:10 by jradioac          #+#    #+#             */
/*   Updated: 2021/03/31 17:12:26 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static int	ft_p(int flag)
{
	if (flag == -1)
		return (0);
	else if (flag == 1)
		return (-1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int		flag;
	int		res;
	int		p;

	flag = 1;
	res = 0;
	p = 0;
	while ((*str == ' ') || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			flag = -flag;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		p++;
		str++;
		if (p > 19)
			return (ft_p(flag));
	}
	return (res * flag);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:55:01 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/01 17:03:18 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, t_all *all, char func, char *arg)
{
	if (func == 'e')
	{
		str = ft_strjoin("minishell: export: `", arg);
		str = ft_strjoin2(str, "': not a valid identifier\n");
	}
	else if (func == 'u')
	{
		str = ft_strjoin("minishell: unset: `", arg);
		str = ft_strjoin2(str, "': not a valid identifier\n");
	}
	else if (func == 'c')
	{
		str = ft_strjoin("minishell: cd: ", arg);
		str = ft_strjoin2(str, ": No such file or directory\n");
	}
	else
		str = ft_strdup("minishell: malloc error: can't allocate region\n");
	str == NULL ? errm() : 0;
	write(2, str, ft_strlen(str));
	all->g_exit = 1;
	free(str);
}

int		errm(void)
{
	write(2, "minishell: malloc error: can't allocate region\n", 47);
	return (1);
}

int		check_error2(t_all *all, char *arg, char func, char *str)
{
	int		j;

	j = 0;
	while (arg[j] != '\0')
	{
		if (ft_strchr("!~,.@#$^%&*-+", arg[j]))
		{
			ft_error(str, all, func, arg);
			return (1);
		}
		j++;
	}
	if (func == 'u' && ft_strchr(arg, '=') != 0)
	{
		ft_error(str, all, func, arg);
		return (1);
	}
	return (0);
}

int		check_error(t_all *all, char **arg, char func)
{
	int		i;
	int		j;
	char	*str;

	i = 1;
	j = 0;
	str = NULL;
	while (arg[i] != NULL)
	{
		if (!(ft_isalpha(arg[i][0])) && arg[i][0] != '_')
		{
			all->g_exit = 1;
			ft_error(str, all, func, arg[i]);
			return (1);
		}
		else
		{
			if (check_error2(all, arg[i], func, str))
				return (1);
		}
		i++;
	}
	all->g_exit = 0;
	return (0);
}

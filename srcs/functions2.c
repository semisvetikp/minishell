/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:17:06 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/01 17:24:30 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_n(char *arg, int *print_arg, int *print_n)
{
	int		j;
	int		len;

	j = 1;
	len = ft_strlen(arg);
	if ((ft_strncmp(arg, "-n", 2) == 0))
	{
		*print_n = 0;
		while (arg[j] == 'n')
			j++;
		if (j == (len))
			*print_arg = 0;
		else
			*print_arg = 1;
	}
	else
		*print_arg = 1;
	return (0);
}

char		*ft_echo2(char **arg, char *str, int print_arg)
{
	int		i;
	int		print_n;

	i = 1;
	print_n = 1;
	while (arg[i] != NULL)
	{
		check_n(arg[i], &print_arg, &print_n);
		if (print_arg == 1)
		{
			(str = ft_strjoin2(str, arg[i])) == NULL ? errm() : 0;
			i++;
			break ;
		}
		i++;
	}
	while (arg[i] != NULL)
	{
		(str = ft_strjoin2(str, " ")) == NULL ? errm() : 0;
		(str = ft_strjoin2(str, arg[i])) == NULL ? errm() : 0;
		i++;
	}
	if (print_n == 1 && str != NULL)
		str = ft_strjoin2(str, "\n");
	return (str);
}

char		*ft_echo(t_all *all, char **arg)
{
	int		i;
	int		print_arg;
	char	*str;

	i = 1;
	print_arg = 0;
	(str = ft_strdup("")) == NULL ? errm() : 0;
	if (arg[1] == NULL)
	{
		free(str);
		(str = ft_strdup("\n")) == NULL ? errm() : 0;
		return (str);
	}
	str = ft_echo2(arg, str, print_arg);
	all->g_exit = 0;
	return (str);
}

void		ft_exit(t_all *all, int code)
{
	write(1, "exit\n", 5);
	all->g_exit = code;
	exit(all->g_exit);
}

char		*pwd(t_all *all, t_env *env, int flag)
{
	char *str;

	str = NULL;
	(void)env;
	(str = getcwd(NULL, 0)) == NULL ? errm() : 0;
	all->g_exit = 0;
	if (flag != 1)
		(str = ft_strjoin2(str, "\n")) == NULL ? errm() : 0;
	return (str);
}

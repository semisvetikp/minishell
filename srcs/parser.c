/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:03:15 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/03 02:04:08 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handling_exit(t_all *all, char **args)
{
	if (args[1] == NULL)
		ft_exit(all, 0);
	else
	{
		if ((onlydigit(args[1]) || (args[1][0] == '+'
		&& onlydigit(&args[1][1]))) && args[2] == NULL)
			ft_exit(all, ft_atoi(args[1]));
		else if (args[1][0] == '-' && onlydigit(&args[1][1]) && args[2] == NULL)
			ft_exit(all, (256 - ft_atoi(&args[1][1])));
		else if (onlydigit(args[1]) && args[2] != NULL)
		{
			write(2, "exit\nminishell: exit: too many arguments\n", 41);
			all->g_exit = 1;
			return ;
		}
		else
		{
			write(2, "minishell: exit: ", 17);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 28);
			ft_exit(all, 255);
		}
	}
}

char		*choose_cmd(t_all *all, char *line)
{
	char	*str;

	str = NULL;
	if ((ft_strcmp(line, "echo") == 0))
		str = ft_echo(all, all->main.array);
	else if ((ft_strcmp(line, "env") == 0))
		str = envp(all, all->env);
	else if ((ft_strcmp(line, "export") == 0))
		str = ft_export(all->env, all->main.array, all);
	else if ((ft_strcmp(line, "unset") == 0))
		str = unset(all, &all->env, all->main.array);
	else if ((ft_strcmp(line, "pwd") == 0))
		str = pwd(all, all->env, 0);
	else if ((ft_strcmp(line, "cd") == 0))
		str = cd(all->env, all->main.array, all);
	else if ((ft_strcmp(line, "exit") == 0))
		handling_exit(all, all->main.array);
	else
		all->pip == 0 ? launch(all->main.array, all) :
					launch_pipe(all->main.array, all);
	return (str);
}

int			preparser(char *line, t_all *all, int i)
{
	squeeze(line, -6);
	squeeze(line, -7);
	squeeze(line, '\\');
	i = 0;
	line = pars_check_redir(line, all);
	if (all->redir.type != 0 || all->redir.read != NULL)
	{
		if (redirect_execve(all->redir, all))
		{
			free_null_redirect(all);
			return (1);
		}
	}
	if ((all->main.array = ft_split(line, ' ')) == NULL)
		return (1);
	line = free_null(line);
	if (all->main.array == NULL || all->main.array[0] == NULL)
		return (1);
	while (all->main.array[i])
	{
		decoder(all->main.array[i]);
		i++;
	}
	return (0);
}

int			parser1(char *line, t_all *all)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	preparser(line, all, i);
	if (all->main.array != NULL)
		str = choose_cmd(all, all->main.array[0]);
	if (str != NULL && (all->redir.type != 0 || all->redir.read != NULL))
		ft_putstr_fd(str, all->fd.fd1);
	if (str != NULL && (all->redir.argwrite == NULL))
		write(1, str, ft_strlen(str));
	all->main.array = clear_split(all->main.array);
	if (all->redir.type != 0 || all->redir.read != NULL)
		free_null_redirect(all);
	str = free_null(str);
	return (0);
}

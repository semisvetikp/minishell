/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daughter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:37:54 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/03 02:41:50 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*check_exec(char **args, t_all *all)
{
	char	*p;

	if (args[0][0] == '/')
		p = check_aout(args[0], all);
	else if ((args[0][0] == '.' && args[0][1] == '/') ||
				(ft_strcmp(args[0], "minishell")) == 0)
		p = check_aout(args[0], all);
	else
		p = choose_path(args[0], all, -1);
	if (p == NULL)
		return (NULL);
	return (p);
}

static void	launch_fork2(pid_t pid, t_all *all)
{
	int status;

	waitpid(pid, &status, 0);
	if (status == 2)
		all->g_exit = 130;
	else if (status == 3)
		all->g_exit = 131;
	else if (status != 0 && status != 256)
		all->g_exit = status >> 8;
	else if (status == 256)
		all->g_exit = 1;
	else
		all->g_exit = 0;
}

int			launch(char **args, t_all *all)
{
	pid_t	pid;
	char	*p;

	if ((p = check_exec(args, all)) == NULL)
		return (1);
	all->menv = array_env(all->env);
	if (ft_strcmp(p, "/usr/bin/wc") == 0 || ft_strcmp(p, "/bin/cat") == 0)
		g_fork = 1;
	pid = fork();
	if (pid == 0)
	{
		if (all->redir.type == '>' || all->redir.type == -20)
			dup2(all->fd.fd1, 1);
		if (all->redir.argread != NULL)
			dup2(all->fd.fd0, 0);
		execve(p, args, all->menv);
		exit(1);
	}
	else
		launch_fork2(pid, all);
	clear_split(all->menv);
	p = free_null(p);
	return (1);
}

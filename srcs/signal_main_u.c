/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:10:24 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/01 23:10:32 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sigint(int sig)
{
	pid_t	pid;

	(void)sig;
	pid = waitpid(-1, NULL, WNOHANG);
	if (g_fork == 1)
		write(1, "\n", 1);
	else if (pid == -1 && g_fork == 0)
	{
		write(1, "\b\b  \b\b\n", 7);
		write(1, "minishell$ ", 11);
	}
	g_fork = 0;
}

void		sigquit(int sig)
{
	pid_t	pid;

	(void)sig;
	pid = waitpid(-1, NULL, WNOHANG);
	if (g_fork == 1)
		write(1, "Quit: 3\n", 8);
	g_fork = 0;
}

void		make_environment_variable(t_all *all, char **envp)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = all->env;
	all->cd = malloc(sizeof(t_cd));
	while (envp[i] != NULL)
	{
		tmp = ft_envadd_back(&all->env, ft_envnew());
		fill_env(tmp, envp[i], all);
		if (ft_strncmp("OLDPWD", envp[i], 6) == 0)
			tmp->id = 3;
		else if ((ft_strcmp(tmp->key, "_")) == 0)
			tmp->id = 4;
		else
			tmp->id = 1;
		i++;
	}
}

void		init_structure(t_all *all)
{
	all->fd.tmpfd = dup(0);
	all->redir.type = 0;
	all->env = NULL;
	all->redir.argread = NULL;
	all->redir.argwrite = NULL;
	all->redir.addwrite = NULL;
	all->redir.create = NULL;
	all->redir.read = NULL;
}

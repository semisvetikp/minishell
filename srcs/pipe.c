/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 00:49:17 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/02 01:40:19 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			launch_pipe(char **args, t_all *all)
{
	char	**evp;
	char	*p;

	if ((p = check_exec(args, all)) == NULL)
		return (1);
	evp = array_env(all->env);
	if (execve(p, args, evp) == -1)
	{
		p = free_null(p);
		return (1);
	}
	p = free_null(p);
	return (0);
}

void		do_pipe_exec(char *str, t_all *all)
{
	if (all->redir.type == '>' || all->redir.type == -20)
		dup2(all->fd.fd1, 1);
	if (all->redir.read != NULL)
		dup2(all->fd.fd0, 0);
	if (all->redir.argwrite == NULL)
	{
		dup2(all->fd.pfd[1], 1);
		close(all->fd.pfd[0]);
	}
	str = choose_cmd(all, all->main.array[0]);
	if (str != NULL)
		write(1, str, ft_strlen(str));
	close(all->fd.pfd[1]);
	exit(1);
}

int			pre_do_pipe(char *line, t_all *all)
{
	int		i;

	i = 0;
	squeeze(line, -6);
	squeeze(line, -7);
	line = pars_check_redir(line, all);
	if (all->redir.type != 0 || all->redir.read != NULL)
		if (redirect_execve(all->redir, all))
		{
			if (all->redir.type != 0)
				free_null_redirect(all);
			line = free_null(line);
			return (0);
		}
	all->main.array = ft_split(line, ' ');
	line = free_null(line);
	if (all->main.array[0] == NULL || all->main.array == NULL)
		return (1);
	while (all->main.array[i])
	{
		decoder(all->main.array[i]);
		i++;
	}
	return (0);
}

int			do_pipe(char *line, t_all *all)
{
	char	*str;
	pid_t	pid;

	str = NULL;
	if (pre_do_pipe(line, all))
		return (1);
	pid = fork();
	if (pid == 0)
		do_pipe_exec(str, all);
	else
	{
		dup2(all->fd.pfd[0], 0);
		close(all->fd.pfd[1]);
		wait(&all->g_exit);
		all->g_exit = 0;
		close(all->fd.pfd[0]);
	}
	if (all->redir.type != 0)
		free_null_redirect(all);
	str = free_null(str);
	clear_split(all->main.array);
	return (0);
}

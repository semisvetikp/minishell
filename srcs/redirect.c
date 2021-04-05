/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 00:50:25 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/02 01:09:23 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_redirect3(t_redir redir, t_all *all)
{
	int	i;
	int tmpfd;

	i = 0;
	if (redir.read != NULL)
	{
		while (redir.read[i] != NULL)
		{
			decoder(&redir.read[i][0]);
			squeeze(redir.read[i], '\\');
			tmpfd = open(redir.read[i], O_RDONLY);
			if (tmpfd == -1)
			{
				write(1, "minishell: ", 11);
				write(1, redir.read[i], ft_strlen(redir.read[i]));
				write(1, ": No such file or directory\n", 28);
				all->g_exit = 1;
				return (1);
			}
			close(tmpfd);
			i++;
		}
	}
	return (0);
}

int		check_redirect2(t_redir red)
{
	int	i;
	int tmpfd;

	i = 0;
	if (red.addwrite != NULL)
	{
		while (red.addwrite[i] != NULL)
		{
			decoder(&red.addwrite[i][0]);
			squeeze(red.addwrite[i], '\\');
			tmpfd = open(red.addwrite[i], O_CREAT | O_APPEND | O_RDWR, 0644);
			close(tmpfd);
			i++;
		}
	}
	return (0);
}

int		check_redirect(t_redir redir, t_all *all)
{
	int i;
	int tmpfd;

	i = 0;
	if (redir.create != NULL)
	{
		while (redir.create[i] != NULL)
		{
			decoder(&redir.create[i][0]);
			squeeze(redir.create[i], '\\');
			tmpfd = open(redir.create[i], O_CREAT | O_TRUNC | O_RDWR, 0644);
			close(tmpfd);
			i++;
		}
	}
	if (check_redirect2(redir))
		return (1);
	if (check_redirect3(redir, all))
		return (1);
	return (0);
}

int		redirect_execve2(t_redir rd, t_all *all)
{
	if (all->redir.type == -20)
	{
		all->fd.fd1 = open(rd.argwrite, O_RDONLY);
		if (all->fd.fd1 == -1)
			all->fd.fd1 = open(rd.argwrite, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			all->fd.fd1 = open(rd.argwrite, O_CREAT | O_APPEND | O_RDWR, 0644);
	}
	if (rd.argread != NULL)
	{
		decoder(&rd.argread[0]);
		squeeze(rd.argread, '\\');
		all->fd.fd0 = open(rd.argread, O_RDONLY);
		if (all->fd.fd0 == -1)
		{
			write(2, "minishell: ", 11);
			write(2, rd.argread, ft_strlen(rd.argread));
			write(2, ": No such file or directory\n", 28);
			all->g_exit = 1;
			return (1);
		}
	}
	return (0);
}

int		redirect_execve(t_redir red, t_all *all)
{
	int i;

	i = 0;
	if (all->redir.type == '>' || all->redir.type == -20)
	{
		decoder(&red.argwrite[0]);
		squeeze(red.argwrite, '\\');
	}
	if (check_redirect(red, all))
		return (1);
	if (all->redir.type == '>')
		all->fd.fd1 = open(red.argwrite, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (redirect_execve2(red, all))
		return (1);
	all->g_exit = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daughter2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 02:40:55 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/03 02:44:02 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	printerrd(char *args0, t_all *all, int flag)
{
	write(2, "minishell: ", 11);
	write(2, args0, ft_strlen(args0));
	if (flag == 1)
	{
		write(2, ": No such file or directory\n", 29);
		all->g_exit = 126;
	}
	else if (flag == 2)
	{
		write(2, ": command not found\n", 20);
		all->g_exit = 127;
	}
	return (1);
}

char		*choose_path(char *args0, t_all *all, int i)
{
	char	**mass;
	char	*p;
	int		fd;

	if (((mass = ft_split(all->cd->path->content, ':')) == NULL)
			&& printerrd(args0, all, 2))
		return (NULL);
	while (mass[++i] != NULL)
	{
		p = ft_strjoin(mass[i], "/");
		p = ft_strjoin2(p, args0);
		fd = open(p, O_RDONLY);
		if (fd != -1)
			break ;
		p = free_null(p);
	}
	if (fd == -1 || mass[0] == NULL)
	{
		printerrd(args0, all, 2);
		clear_split(mass);
		return (NULL);
	}
	clear_split(mass);
	return (p);
}

char		*check_aout2(char *args0, t_all *all, struct stat buf, char *p)
{
	if (!(S_IXUSR & buf.st_mode))
	{
		write(2, "minishell: Permission denied\n", 29);
		all->g_exit = 126;
		p = free_null(p);
		return (NULL);
	}
	if (S_IFDIR & buf.st_mode)
	{
		write(2, "minishell: ", 11);
		write(2, args0, ft_strlen(args0));
		write(2, ": is a directory\n", 17);
		all->g_exit = 126;
		p = free_null(p);
		return (NULL);
	}
	return (p);
}

char		*check_aout(char *args0, t_all *all)
{
	int			fd;
	char		*p;
	struct stat	buf;

	p = NULL;
	stat(args0, &buf);
	fd = open(args0, O_RDONLY);
	if (ft_strcmp(args0, "minishell") == 0)
	{
		p = ft_strjoin("./", args0);
		close(fd);
		fd = open(p, O_RDONLY);
	}
	close(fd);
	if (fd == -1)
	{
		printerrd(args0, all, 1);
		return (NULL);
	}
	p = free_null(p);
	(p = ft_strdup(args0)) == NULL ? errm() : 0;
	if ((p = check_aout2(args0, all, buf, p)) == NULL)
		return (NULL);
	return (p);
}

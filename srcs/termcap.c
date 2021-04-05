/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:05:48 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/01 23:05:53 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*read_bash_history(t_all *all)
{
	char		str[2000];
	char		*st_str;
	int			fd;
	int			rb;
	char		*path;

	st_str = (char *)ft_calloc(1, 1);
	str[0] = '\0';
	st_str[0] = '\0';
	path = ft_strjoin(all->main.path_history, "/.bash_history");
	fd = open(path, O_RDONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	free(path);
	while ((rb = read(fd, str, 2000)) > 0)
	{
		str[rb] = '\0';
		st_str = ft_strjoin2(st_str, str);
	}
	close(fd);
	return (st_str);
}

int				write_to_bash_history(char *str, t_all *all)
{
	int			fd;
	char		*path;

	path = ft_strjoin(all->main.path_history, "/.bash_history");
	fd = open(path, O_WRONLY | O_APPEND);
	free(path);
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 22:21:05 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/03 02:29:44 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			check_redir(char *line, int i)
{
	while (line[i])
	{
		if ((line[i] == '>' || line[i] == '<') && line[i + 1] == '\0')
			return (1);
		if (line[i] == '>' && line[i + 1] == ' ')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '<' || line[i] == '>')
				return (1);
		}
		if (line[i] != ' ' && line[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

void				free_null_redirect(t_all *all)
{
	all->redir.type = 0;
	if (all->redir.read != NULL)
		all->redir.argread = free_null(all->redir.argread);
	if (all->redir.argwrite != NULL)
		all->redir.argwrite = free_null(all->redir.argwrite);
	if (all->redir.create != NULL)
	{
		clear_split(all->redir.create);
		all->redir.create = NULL;
	}
	if (all->redir.read != NULL)
	{
		clear_split(all->redir.read);
		all->redir.read = NULL;
	}
	if (all->redir.addwrite != NULL)
	{
		clear_split(all->redir.addwrite);
		all->redir.addwrite = NULL;
	}
}

static int			valid_redir2(char *line, t_all *all, int i)
{
	int				same;

	if (line[i] == '<')
	{
		if (check_redir(line, i) == 1)
			return (syntax_error("<", all));
		same = count_same_chr(line, i, '<', -1);
		if (same > 1)
			return (syntax_error(">", all));
	}
	if (line[i] == '>' && line[i + 1] == ' ')
	{
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == '<')
			return (syntax_error("<", all));
	}
	return (0);
}

int					valid_redir(char *line, t_all *all)
{
	int				i;
	int				same;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '>' && line[i - 1] != '\\')
		{
			if (check_redir(line, i) == 1)
				return (syntax_error(">", all));
			same = count_same_chr(line, i, '>', 1);
			if (same > 2 && !(same % 2))
				return (syntax_error(">>", all));
			if (same > 2 && (same % 2))
				return (syntax_error(">", all));
		}
		if (valid_redir2(line, all, i) == -1)
			return (-1);
	}
	return (0);
}

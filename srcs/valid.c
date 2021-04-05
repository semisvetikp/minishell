/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:05:14 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/03 02:09:52 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				valid_semicolon(char *line, t_all *all)
{
	char		*next;
	char		*str;
	char		*begin;

	str = ft_strdup(line);
	begin = str;
	next = ft_strchr(str, ';');
	while (next != NULL)
	{
		*next = '\0';
		if (*(next + 1) == ';')
			return (spec_syntax_error(";;", begin, all));
		if (*(next + 1) == '|')
			return (spec_syntax_error("|", begin, all));
		if (ft_strlen(str) == get_space_count(str))
			return (spec_syntax_error(";", begin, all));
		str = next + 1;
		next = ft_strchr(str, ';');
	}
	free(begin);
	return (0);
}

int				valid_pipe(char *line, t_all *all)
{
	char		*next;
	char		*str;
	char		*begin;

	str = ft_strdup(line);
	begin = str;
	next = ft_strchr(str, '|');
	while (next != NULL)
	{
		*next = '\0';
		if (*(next + 1) == '|')
			return (spec_syntax_error("||", begin, all));
		if (*(next + 1) == ';')
			return (spec_syntax_error(";", begin, all));
		if (ft_strlen(str) == get_space_count(str))
			return (spec_syntax_error("|", begin, all));
		str = next + 1;
		next = ft_strchr(str, '|');
	}
	free(begin);
	return (0);
}

int				split_pipe(char *line, t_all *all)
{
	int			i;
	char		**split;
	int			p;

	i = 0;
	p = count_c(line, '|');
	split = split_arg(line, '|');
	p >= 1 ? all->pip = 1 : 0;
	while (split[i])
	{
		if (all->pip == 1)
		{
			if ((pipe(all->fd.pfd)) != 0)
				return (1);
			if (do_pipe(split[i], all))
				return (1);
		}
		else
			parser1(split[i], all);
		i == p - 1 ? all->pip = 0 : 0;
		i++;
	}
	dup2(all->fd.tmpfd, 0);
	clear_split(split);
	return (0);
}

char			*str_replace(char *line, t_all *all)
{
	int			i;
	int			dollar;
	char		*str;

	i = 0;
	dollar = count_c(line, '$') + count_c(line, '~');
	str = ft_strdup(line);
	while (i != dollar)
	{
		str = replace_env(str, all);
		i++;
	}
	return (str);
}

int				split_line(char *line, t_all *all)
{
	int			j;
	char		*str;
	char		**split;

	j = 0;
	if (check_line(line, all) == -1)
		return (1);
	if (valid_line(line, all) != 0)
		return (1);
	check_escape(&line[0]);
	split = split_arg(line, ';');
	while (split[j])
	{
		str = str_replace(split[j], all);
		if (str != NULL && ft_strchr(str, '|') != 0)
			split_pipe(str, all);
		else if (str != NULL)
			parser1(str, all);
		if (str != NULL)
			free(str);
		j++;
	}
	clear_split(split);
	return (0);
}

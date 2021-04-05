/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 01:11:01 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/03 02:46:28 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			last_write_redirect(char *line, t_all *all, int i)
{
	int		n;
	int		j;
	int		length;

	n = i;
	j = i;
	while (line[j] != ' ' && line[j] != '\0' && line[j] != -7 && line[j] != '|')
		j++;
	length = j - n;
	all->redir.argwrite = (char *)malloc(sizeof(char) * (length + 1));
	if (all->redir.argwrite == NULL)
	{
		errm();
		return ;
	}
	i = 0;
	while (length > 0)
	{
		all->redir.argwrite[i++] = line[n++];
		length--;
	}
	all->redir.argwrite[i] = '\0';
}

void			check_last_write_redirect(char *line, t_all *all)
{
	int		n;
	int		i;
	int		j;

	n = count_c(line, '>') + count_c(line, -20);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == -20)
			j++;
		if (j == n)
			break ;
		++i;
	}
	++i;
	while (line[i] == ' ' || line[i] == -19)
		i++;
	last_write_redirect(line, all, i);
}

char			*pars_check_redir3(char *str, t_all *all)
{
	int		red;

	if (ft_strchr(str, -20) != 0)
	{
		red = count_c(str, -20);
		if ((all->redir.addwrite = malloc(sizeof(char *) * red + 1)) == NULL)
		{
			errm();
			return (NULL);
		}
		all->redir.addwrite[red] = NULL;
		all->j = 0;
		while (all->j < red)
		{
			str = parse_redir(str, all, red, -20);
			all->j++;
		}
	}
	squeeze(&str[0], -20);
	squeeze(&str[0], -19);
	squeeze(&str[0], -21);
	return (str);
}

char			*pars_check_redir2(char *str, t_all *all)
{
	int		red;

	if (ft_strchr(str, '>') != 0)
	{
		red = count_c(str, '>');
		if ((all->redir.create = malloc(sizeof(char *) * red + 1)) == NULL)
		{
			errm();
			return (NULL);
		}
		all->redir.create[red] = NULL;
		all->j = 0;
		while (all->j < red)
		{
			str = parse_redir(str, all, red, '>');
			all->j++;
		}
	}
	if ((str = pars_check_redir3(str, all)) == NULL)
		return (NULL);
	return (str);
}

char			*pars_check_redir(char *line, t_all *all)
{
	int		r;
	char	*str;

	if (count_redir(line) == -1)
		return (NULL);
	str = ft_strdup(line);
	if (ft_strchr(str, '>') != 0 || ft_strchr(str, -20) != 0)
		check_last_write_redirect(line, all);
	if (ft_strchr(str, '<') != 0)
	{
		r = count_c(str, '<');
		if ((all->redir.read = malloc(sizeof(char *) * r + 1)) == NULL)
			return (NULL);
		all->redir.read[r] = NULL;
		all->j = -1;
		while (++all->j < r)
		{
			str = parse_redir(str, all, r, '<');
			if (all->redir.read[all->j + 1] == NULL)
				all->redir.argread = ft_strdup(all->redir.read[all->j]);
		}
	}
	str = pars_check_redir2(str, all);
	return (str);
}

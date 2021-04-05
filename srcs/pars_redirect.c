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

void			init_red(t_replace *rep, int last)
{
	rep->i = 0;
	rep->start = 0;
	rep->end = 0;
	rep->length = 0;
	rep->key = NULL;
	rep->line_copy = NULL;
	rep->last = last;
}

void			key_red(char *line, t_replace *rep, int c, t_all *all)
{
	while (line[rep->i])
	{
		if ((line[rep->i] == c)
			&& line[rep->i - 1] != '\\' && line[rep->i] != '\0')
		{
			if (all->j == rep->last - 1)
				all->redir.type = line[rep->i];
			line[rep->i] = -18;
			rep->i++;
			while (line[rep->i] == ' '
				|| line[rep->i] == -19 || line[rep->i] == -21)
				rep->i++;
			rep->start = rep->i;
			rep->end = rep->i;
			while (line[rep->end] != ' ' && line[rep->end] != '\0'
				&& line[rep->end] != -7
				&& line[rep->end] != '|' && line[rep->end] != '>')
				rep->end++;
			rep->length = rep->end - rep->start;
			break ;
		}
		rep->i++;
	}
}

char			*parse_redir(char *line, t_all *all, int last, char c)
{
	t_replace	rep;

	init_red(&rep, last);
	key_red(line, &rep, c, all);
	rep.key = (char *)malloc(sizeof(char) * (rep.length + 1));
	rep.line_copy = (char *)malloc(sizeof(char) * (rep.start + 1));
	ft_strlcpy2(rep.line_copy, line, rep.start);
	rep.i = 0;
	while (rep.length--)
		rep.key[rep.i++] = line[rep.start++];
	rep.key[rep.i] = '\0';
	squeeze(&rep.line_copy[0], -18);
	squeeze(&rep.key[0], -18);
	if (c == '>')
		all->redir.create[all->j] = ft_strdup(rep.key);
	if (c == -20)
		all->redir.addwrite[all->j] = ft_strdup(rep.key);
	if (c == '<')
		all->redir.read[all->j] = ft_strdup(rep.key);
	rep.line_copy = ft_strjoin2(rep.line_copy, &line[rep.end]);
	squeeze(&rep.line_copy[0], -18);
	ft_strclr(line);
	rep.key = free_null(rep.key);
	line = free_null(line);
	return (rep.line_copy);
}

int				count_redir(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '>' && line[i + 1] == '>')
		{
			line[i] = -20;
			line[i + 1] = -19;
		}
		if (line[i] == '<' && line[i + 1] == '>')
			line[i] = -21;
		if (line[i] == '>' || line[i] == -20 ||
		(line[i] == '<' && line[i + 1] != '>'))
			count++;
		i++;
	}
	return (count);
}

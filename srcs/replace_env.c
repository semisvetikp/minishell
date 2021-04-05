/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:04:30 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/03 02:10:38 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_env(t_replace *rep)
{
	rep->i = 0;
	rep->start = 0;
	rep->end = 0;
	rep->length = 0;
	rep->key = NULL;
	rep->line_copy = NULL;
}

void			search_key(char *line, t_replace *rep)
{
	init_env(rep);
	while (line[rep->i])
	{
		if (line[rep->i] == '$')
		{
			rep->i++;
			rep->start = rep->i;
			rep->end = rep->i;
			while (ft_isalnum(line[rep->end]) ||
				line[rep->end] == '_' || line[rep->end] == '?')
				rep->end++;
			rep->length = rep->end - rep->start;
			break ;
		}
		else if (line[rep->i] == '~' && (line[rep->i + 1] == ' ' ||
			line[rep->i + 1] == '\0' || line[rep->i + 1] == '/'))
		{
			rep->length = 1;
			rep->start = rep->i;
			rep->end = rep->i + 1;
			break ;
		}
		rep->i++;
	}
}

void			replace_key(char *line, t_replace *rep, t_all *all, t_env *tmp)
{
	char *itoa;

	itoa = NULL;
	if (line[rep->i] == '~')
		rep->line_copy = ft_strjoin2(rep->line_copy, " ");
	rep->i = 0;
	while (rep->length--)
		rep->key[rep->i++] = line[rep->start++];
	rep->key[rep->i] = '\0';
	if (ft_strcmp(rep->key, "?") == 0)
	{
		itoa = ft_itoa(all->g_exit);
		rep->line_copy = ft_strjoin2(rep->line_copy, itoa);
		free(itoa);
	}
	else if (ft_strcmp(rep->key, "~") == 0)
		rep->line_copy = ft_strjoin2(rep->line_copy, all->main.home);
	else
		while (tmp)
		{
			if (ft_strcmp(rep->key, tmp->key) == 0)
				rep->line_copy = ft_strjoin2(rep->line_copy, tmp->content);
			tmp = tmp->next;
		}
}

char			*replace_env(char *line, t_all *all)
{
	t_replace	rep;
	t_env		*tmp;

	tmp = all->env;
	search_key(line, &rep);
	rep.key = (char *)malloc(sizeof(char) * (rep.length + 1));
	rep.line_copy = (char *)malloc(sizeof(char) * (rep.start + 1));
	ft_strlcpy2(rep.line_copy, line, rep.start);
	replace_key(line, &rep, all, tmp);
	rep.line_copy = ft_strjoin2(rep.line_copy, &line[rep.end]);
	ft_strclr(line);
	free(rep.key);
	free(line);
	line = NULL;
	return (rep.line_copy);
}

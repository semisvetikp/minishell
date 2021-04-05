/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:45:38 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/02 15:45:43 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		xyeta(char *envp, t_all *all, t_env *tmp, int i)
{
	char *s;

	s = ft_strdup(envp);
	if ((ft_strncmp(s, "SHLVL", 5)) == 0 || ft_strncmp("PWD", s, 3) == 0
		|| (ft_strncmp("HOME=", s, 5)) == 0 || ft_strncmp("OLDPWD", s, 6) == 0
		|| ft_strncmp("PATH", s, 4) == 0)
		remind_cd(all, s, tmp, i);
	else if ((ft_strcmp(tmp->key, "_")) == 0)
		tmp->content = ft_strdup("/usr/bin/env");
	else
		tmp->content = ft_strdup(&s[i]);
	free(s);
}

void		fill_env(t_env *env, char *envp, t_all *all)
{
	t_env	*tmp;
	char	*s;
	int		i;

	i = 0;
	tmp = env;
	s = ft_strdup(envp);
	if ((ft_strchr(s, '=')) != NULL)
	{
		while (s[i] != '=')
			i++;
		s[i] = '\0';
	}
	tmp->key = ft_strdup(s);
	free(s);
	i++;
	if ((ft_strchr(envp, '=')) != NULL)
		xyeta(envp, all, tmp, i);
}

void		list_init(t_sl *sl)
{
	sl->i = 0;
	sl->lise_list_start = 0;
	sl->prev_line = NULL;
}

t_lines		*ft_split_to_line_list(char *str)
{
	t_sl sl;

	list_init(&sl);
	if (str == NULL)
		return (sl.lise_list_start);
	while (str[sl.i] != '\0')
	{
		sl.start = sl.i;
		while (!ft_ch_is_in_str(str[sl.i], "\n") && str[sl.i] != '\0')
			sl.i++;
		if (sl.start != sl.i)
		{
			sl.curr_line = ft_lines_new_empty();
			sl.curr_line->line = ft_substr(str, sl.start, sl.i - sl.start);
			sl.curr_line->prev = sl.prev_line;
			ft_lines_add_back(&sl.lise_list_start, sl.curr_line);
			sl.prev_line = sl.curr_line;
		}
		str[sl.i] != '\0' ? sl.i++ : 0;
	}
	sl.curr_line = ft_lines_new_empty();
	sl.curr_line->line = (char *)ft_calloc(1, 1);
	sl.curr_line->prev = sl.prev_line;
	ft_lines_add_back(&sl.lise_list_start, sl.curr_line);
	return (sl.lise_list_start);
}

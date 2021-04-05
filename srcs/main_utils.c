/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:31:43 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/01 23:31:47 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		t_term_to_cannon(t_all *all, char *name)
{
	tcgetattr(0, &all->term);
	all->term.c_lflag |= ECHO;
	all->term.c_lflag |= ICANON;
	all->term.c_lflag |= ISIG;
	tcsetattr(0, TCSANOW, &all->term);
	tgetent(0, name);
}

void		help_remind_cd_home(t_env *tmp, int i, t_all *all, char *s)
{
	(tmp->content = ft_strdup(&s[i])) == NULL ? errm() : 0;
	all->cd->home = tmp;
	(all->main.home = ft_strdup(tmp->content)) == NULL ? errm() : 0;
}

void		help_remind_cd_path(t_env *tmp, int i, t_all *all, char *s)
{
	(tmp->content = ft_strdup(&s[i])) == NULL ? errm() : 0;
	all->cd->path = tmp;
}

void		remind_cd(t_all *all, char *s, t_env *tmp, int i)
{
	int		at;
	char	*itoa;

	if ((ft_strncmp(s, "SHLVL", 5)) == 0)
	{
		at = ft_atoi(&s[i]) + 1;
		itoa = ft_itoa(at);
		(tmp->content = ft_strdup(itoa)) == NULL ? errm() : 0;
		free(itoa);
	}
	if ((ft_strncmp("PWD", s, 3)) == 0)
	{
		(tmp->content = ft_strdup(&s[i])) == NULL ? errm() : 0;
		all->cd->pwd = tmp;
		(all->main.path_history = ft_strdup(tmp->content)) == NULL ? errm() : 0;
	}
	if ((ft_strncmp("OLDPWD", s, 6)) == 0)
	{
		tmp->content = ft_strdup(&s[i]);
		all->cd->oldpwd = tmp;
	}
	if ((ft_strncmp("HOME=", s, 5)) == 0)
		help_remind_cd_home(tmp, i, all, s);
	if ((ft_strncmp("PATH", s, 4)) == 0)
		help_remind_cd_path(tmp, i, all, s);
}

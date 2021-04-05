/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:50:57 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/01 17:15:31 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*cd_path(t_env *env, char *str, t_all *all, char **arg)
{
	if (chdir(all->cd->pwd->content) != 0)
	{
		if (all->cd->pwd->content != NULL && all->cd->home->id != 6)
			free(all->cd->pwd->content);
		all->cd->pwd->content = ft_strdup(all->cd->home->content);
		ft_error(str, all, 'c', arg[1]);
	}
	else if (chdir(arg[1]) == 0)
	{
		str = pwd(all, env, 1);
		if (all->cd->pwd->content != NULL)
			all->cd->oldpwd->id = 1;
		if (all->cd->oldpwd->content != NULL && all->cd->pwd->id != 6)
		{
			free(all->cd->oldpwd->content);
			all->cd->oldpwd->content = ft_strdup(all->cd->pwd->content);
		}
		if (all->cd->pwd->content != NULL)
			free(all->cd->pwd->content);
		(all->cd->pwd->content = ft_strdup(str)) == NULL ? errm() : 0;
		free(str);
	}
	else
		ft_error(str, all, 'c', arg[1]);
	return (NULL);
}

char		*cd_minus(char *str, t_all *all)
{
	int		flag;

	flag = 0;
	if (all->cd->oldpwd->id != 3 && all->cd->oldpwd->content != NULL)
	{
		(str = ft_strdup(all->cd->oldpwd->content)) == NULL ? errm() : 0;
		chdir(str);
		flag = 1;
		free(all->cd->oldpwd->content);
		all->cd->oldpwd->content = ft_strdup(all->cd->pwd->content);
	}
	else
		str = ft_strdup("minishell: cd: OLDPWD not set\n");
	if (flag == 0 && str == NULL)
		str = ft_strdup("minishell: cd: OLDPWD not set\n");
	if (flag == 1)
	{
		free(all->cd->pwd->content);
		(all->cd->pwd->content = ft_strdup(str)) == NULL ? errm() : 0;
		(str = ft_strjoin2(str, "\n")) == NULL ? errm() : 0;
	}
	return (str);
}

char		*cd(t_env *env, char **arg, t_all *all)
{
	char	*str;

	str = NULL;
	if (arg[1] != NULL && (ft_strcmp(arg[1], "-") != 0)
		&& (ft_strcmp(arg[1], "--") != 0))
		str = cd_path(env, str, all, arg);
	else if ((ft_strcmp(arg[1], "-")) == 0)
		str = cd_minus(str, all);
	else if (arg[1] == NULL || ft_strcmp(arg[1], "--") == 0)
	{
		if (all->cd->home->content == NULL)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (NULL);
		}
		chdir(all->cd->home->content);
		str = pwd(all, env, 1);
		free(all->cd->oldpwd->content);
		all->cd->oldpwd->content = ft_strdup(all->cd->pwd->content);
		free(all->cd->pwd->content);
		(all->cd->pwd->content = ft_strdup(str)) == NULL ? errm() : 0;
		all->cd->oldpwd->id = 1;
		str = free_null(str);
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:00:27 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/01 17:30:48 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*envp(t_all *all, t_env *env)
{
	char	*str;

	(str = ft_strdup("")) == NULL ? errm() : 0;
	while (env)
	{
		if (env->id == 1 || env->id == 4)
		{
			str = ft_strjoin2(str, env->key);
			str = ft_strjoin2(str, "=");
			str = ft_strjoin2(str, env->content);
			str = ft_strjoin2(str, "\n");
		}
		env = env->next;
	}
	str == NULL ? errm() : 0;
	all->g_exit = 0;
	return (str);
}

void		unset_cd(t_env *env, char *arg)
{
	while (env)
	{
		if ((ft_strcmp(env->key, arg)) == 0)
		{
			free(env->content);
			env->content = NULL;
			env->id = 6;
		}
		env = env->next;
	}
}

void		unset_too(t_env **env, char *arg)
{
	t_env	*pr;
	t_env	*tmp;

	tmp = *env;
	pr = NULL;
	while (tmp)
	{
		if ((ft_strcmp(tmp->key, arg)) == 0)
			ft_envdelone(env, tmp, pr);
		pr = tmp;
		tmp = tmp->next;
	}
}

char		*unset(t_all *all, t_env **env, char **arg)
{
	int		i;

	i = 1;
	if (check_error(all, arg, 'u'))
		return (NULL);
	while (arg[i] != NULL)
	{
		if (ft_strcmp("HOME", arg[i]) == 0 || ft_strcmp("PWD", arg[i]) == 0
		|| ft_strcmp("OLDPWD", arg[i]) == 0 || ft_strcmp("PATH", arg[i]) == 0)
			unset_cd(*env, arg[i]);
		else
			unset_too(env, arg[i]);
		i++;
	}
	all->g_exit = 0;
	return (NULL);
}

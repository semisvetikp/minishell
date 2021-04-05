/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:20:38 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/02 01:44:43 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**array_env(t_env *env)
{
	char	**mass;
	int		i;
	int		size;
	t_env	*tmp;

	tmp = env;
	i = 0;
	size = ft_envsize(tmp);
	(mass = ft_calloc(size + 1, sizeof(char *))) == NULL ? errm() : 0;
	while (tmp && mass != NULL)
	{
		if (tmp->content != NULL && tmp->id != 3)
		{
			mass[i] = ft_strjoin(tmp->key, "=");
			mass[i] = ft_strjoin2(mass[i], tmp->content);
		}
		else
			mass[i] = ft_strdup(tmp->key);
		i++;
		tmp = tmp->next;
	}
	mass != NULL ? (mass[i] = NULL) : 0;
	return (mass);
}

int			search_env(t_env *env, char *arg)
{
	int		i;
	t_env	*tmp;
	char	*s;

	i = 0;
	tmp = env;
	if ((s = ft_strdup(arg)) == NULL)
		return (errm());
	while (s[i] != '=' && s[i] != '\0')
		i++;
	s[i] = '\0';
	while (tmp)
	{
		if ((ft_strcmp(s, tmp->key)) == 0)
		{
			tmp->content == NULL ? tmp->id = 1 : 0;
			tmp->content != NULL ? free(tmp->content) : 0;
			tmp->content = ft_strdup(&arg[i + 1]);
			s = free_null(s);
			return (1);
		}
		tmp = tmp->next;
	}
	s = free_null(s);
	return (0);
}

void		check_equal(t_env *env, char **arg, t_all *all)
{
	int		i;
	t_env	*tmp;

	i = 1;
	tmp = env;
	while (arg[i] != NULL)
	{
		if ((ft_strchr(arg[i], '=')) != NULL)
		{
			if (!(search_env(env, arg[i])))
			{
				tmp = ft_envadd_back(&env, ft_envnew());
				fill_env(tmp, arg[i], all);
				tmp->id = 1;
			}
		}
		else if (!(search_env(env, arg[i])))
		{
			tmp = ft_envadd_back(&env, ft_envnew());
			fill_env(tmp, arg[i], all);
			tmp->id = 2;
		}
		i++;
	}
	all->g_exit = 0;
}

char		*ft_export(t_env *env, char **arg, t_all *all)
{
	char	*str;
	char	**sort_array;
	int		i;

	str = NULL;
	if ((check_error(all, arg, 'e')))
		return (str);
	check_equal(env, arg, all);
	if (arg[1] == NULL)
	{
		if ((sort_array = sort_env(env, 0)) == NULL)
			return (NULL);
		(str = ft_strdup("")) == NULL ? errm() : 0;
		i = -1;
		while (sort_array[++i] != NULL)
		{
			str = ft_strjoin2(str, "declare -x ");
			str = ft_strjoin2(str, sort_array[i]);
			str = ft_strjoin2(str, "\n");
		}
		clear_split(sort_array);
		return (str);
	}
	else
		return (NULL);
}

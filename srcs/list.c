/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:12:51 by jradioac          #+#    #+#             */
/*   Updated: 2021/03/31 18:00:35 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*ft_envnew(void)
{
	t_env	*elem;

	elem = (t_env *)malloc(sizeof(t_env));
	if (elem != NULL)
	{
		elem->next = NULL;
		elem->key = NULL;
		elem->content = NULL;
	}
	return (elem);
}

t_env		*ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*elem;

	if (*env)
	{
		elem = ft_envlast(*env);
		elem->next = new;
	}
	else
		*env = new;
	return (new);
}

void		ft_envdelone(t_env **env, t_env *tmp, t_env *pr)
{
	if (!tmp || !*env)
		return ;
	if (pr == NULL)
		*env = tmp->next;
	else
		pr->next = tmp->next;
	free(tmp->content);
	free(tmp->key);
	free(tmp);
	tmp = NULL;
}

int			ft_envsize(t_env *env)
{
	t_env	*elem;
	int		k;

	k = 0;
	elem = env;
	while (elem)
	{
		if (elem->id != 6)
			k++;
		elem = elem->next;
	}
	return (k);
}

t_env		*ft_envlast(t_env *env)
{
	t_env	*elem;

	if (env == NULL)
		return (NULL);
	elem = env;
	while (elem->next != NULL)
	{
		elem = elem->next;
	}
	return (elem);
}

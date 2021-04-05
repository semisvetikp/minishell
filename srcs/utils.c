/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 21:43:48 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/03 02:09:14 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		onlydigit(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

char	**sort_env2(int size, char **mass, int i)
{
	int	j;

	mass[i] = NULL;
	size--;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - 1)
			if ((strcmp(mass[j], mass[j + 1])) > 0)
				ft_swap(&mass[j], &mass[j + 1]);
	}
	return (mass);
}

char	**sort_env(t_env *env, int i)
{
	char	**mass;
	int		size;
	t_env	*tmp;

	tmp = env;
	size = ft_envsize(tmp);
	(mass = ft_calloc(size + 1, sizeof(char *))) == NULL ? errm() : 0;
	while (tmp && mass != NULL)
	{
		if (tmp->id != 4 && tmp->id != 6)
		{
			if (tmp->content != NULL && tmp->id != 3)
			{
				mass[i] = ft_strjoin(tmp->key, "=\"");
				mass[i] = ft_strjoin2(mass[i], tmp->content);
				mass[i] = ft_strjoin2(mass[i], "\"");
			}
			else
				mass[i] = ft_strdup(tmp->key);
			i++;
		}
		tmp = tmp->next;
	}
	mass == NULL ? 0 : (mass = sort_env2(size, mass, i));
	return (mass);
}

char	*free_null(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (str);
}

char	**clear_split(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	return (NULL);
}

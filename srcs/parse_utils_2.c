/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:22:22 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/03 02:45:47 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_empty_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}

void		check_escape(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("\\;|><() ", line[i]) && line[i - 1] == '\\')
			coder(&line[0], i, 1);
		if (line[i] == '$' && line[i - 1] == '\\')
			line[i] = -8;
		i++;
	}
}

int			valid_arg(char *line, int c1, int c2)
{
	int		i;
	int		j;
	int		spaces;

	spaces = 0;
	i = 0;
	j = -1;
	while (line[i])
	{
		if (line[i] == c1)
		{
			i++;
			while (line[i] != c2 && line[i])
			{
				(line[i] == ' ') ? spaces++ : 0;
				j++;
				i++;
			}
			j += 1;
		}
		i++;
	}
	if (j == spaces)
		return (1);
	return (0);
}

int			get_space_count(char *line)
{
	int		i;
	int		space;

	i = 0;
	space = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			space++;
		i++;
	}
	return (space);
}

int			c_redir(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' && line[i + 1] == '<')
			return (1);
		if (line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>')
			return (1);
		i++;
	}
	return (0);
}

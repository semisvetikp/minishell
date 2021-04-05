/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 22:18:44 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/03 02:11:46 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		squeeze(char *s, int c)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			s[j] = s[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
}

int			syntax_error(char *error, t_all *all)
{
	if (!error)
		write(2, "Syntax error\n", 13);
	else
	{
		write(2, "minishell: syntax error near unexpected token \0",
		ft_strlen("minishell: syntax error near unexpected token \0"));
		write(2, "`", 1);
		write(2, error, ft_strlen(error));
		ft_putendl_fd("\'", 2);
		all->g_exit = 258;
	}
	return (-1);
}

char		**split_arg(char *line, char c)
{
	char	**arr;

	arr = ft_split(line, c);
	return (arr);
}

int			count_same_chr(char *line, int i, char c, int dir)
{
	int		same;

	same = 0;
	while (line[i] && line[i] == c)
	{
		if (dir == 1)
			i++;
		else if (dir == -1)
			i--;
		same++;
	}
	return (same);
}

int			count_c(char *line, int c)
{
	int		i;
	int		cou;

	i = 0;
	cou = 0;
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		{
			line[i] = -8;
			i++;
		}
		if (line[i] == c)
			cou++;
		i++;
	}
	return (cou);
}

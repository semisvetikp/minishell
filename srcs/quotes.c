/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:36:38 by dmarget           #+#    #+#             */
/*   Updated: 2021/03/31 18:36:48 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_quotes(char *line, int i, t_all *all)
{
	line[i] = -6;
	while (line[++i] != '\'')
	{
		if (!line[i])
			return (syntax_error("\'", all));
		if (line[i] == '$')
			line[i] = -8;
		coder(&line[0], i, 1);
	}
	line[i] = -6;
	return (1);
}

int		is_escape(char *line, int i)
{
	int count_slash;
	int res;

	count_slash = 0;
	while (line[--i])
	{
		if (line[i] == '\\')
			count_slash++;
		else
			break ;
	}
	res = count_slash % 2;
	if (res == 0)
		return (0);
	return (1);
}

int		check_dquotes(char *line, int i, t_all *all)
{
	int		j;
	int		sum;

	j = 0;
	line[i++] = -7;
	while (line[i + j])
	{
		if (line[i] == '\\' && ft_isalpha(line[i + 1]))
			*(line + i) = -11;
		if (line[i + j] == '\"' && !is_escape(line, i + j))
			break ;
		j++;
	}
	if (!line[i + j])
		return (syntax_error("\"", all));
	sum = i + j;
	while (i < sum)
	{
		coder(&line[0], i, 0);
		i++;
	}
	line[i] = -7;
	return (1);
}

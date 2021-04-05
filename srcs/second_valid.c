/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 22:25:34 by dmarget           #+#    #+#             */
/*   Updated: 2021/03/31 22:25:38 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				valid_slash(char *line, t_all *all)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1] == '\0' &&
			line[i + 1] != '\\' && line[i - 1] != '\\')
			return (syntax_error("\\", all));
		i++;
	}
	return (0);
}

int				check_pipe(char *line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int				valid_line(char *line, t_all *all)
{
	if (check_pipe(line) == 1)
		return (syntax_error("newline", all));
	if (c_redir(line) == 1)
		return (syntax_error(">", all));
	if (valid_arg(line, '|', '\0') == 1)
		return (syntax_error("newline", all));
	if (valid_arg(line, '|', ';') == 1)
		return (syntax_error("|", all));
	if (line[0] == '\\')
		return (syntax_error("newline", all));
	if (valid_redir(line, all) == -1)
		return (1);
	if (valid_semicolon(line, all) == -1 ||
		valid_pipe(line, all) == -1 ||
		valid_bracket(line, all) == -1 ||
		valid_slash(line, all) == -1)
		return (1);
	return (0);
}

int				valid_bracket(char *line, t_all *all)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
			return (syntax_error("(", all));
		if (line[i] == ')')
			return (syntax_error(")", all));
		i++;
	}
	return (0);
}

int				check_line(char *line, t_all *all)
{
	int			i;

	i = 0;
	if (check_empty_line(line))
		return (-1);
	while (line[i])
	{
		if (line[i] == '\'' && !is_escape(line, i))
			if (check_quotes(line, i, all) == -1)
				return (-1);
		if (line[i] == '\"' && !is_escape(line, i))
			if (check_dquotes(line, i, all) == -1)
				return (-1);
		i++;
	}
	return (0);
}

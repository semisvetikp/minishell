/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 02:05:53 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/03 02:06:24 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		coder(char *line, int i, int slash)
{
	if (line[i] == ' ')
		line[i] = -1;
	if (line[i] == ';')
		line[i] = -2;
	if (line[i] == '|')
		line[i] = -3;
	if (line[i] == '>')
		line[i] = -4;
	if (line[i] == '<')
		line[i] = -5;
	if (line[i] == '\'')
		line[i] = -9;
	if (line[i] == '\"')
		line[i] = -10;
	if (line[i] == '\\' && slash == 1)
		line[i] = -11;
}

void		decoder(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == -1)
			line[i] = ' ';
		if (line[i] == -2)
			line[i] = ';';
		if (line[i] == -3)
			line[i] = '|';
		if (line[i] == -4)
			line[i] = '>';
		if (line[i] == -5)
			line[i] = '<';
		if (line[i] == -9)
			line[i] = '\'';
		if (line[i] == -10)
			line[i] = '\"';
		if (line[i] == -8)
			line[i] = '$';
		if (line[i] == -11)
			line[i] = '\\';
		i++;
	}
}

int			spec_syntax_error(char *error, char *fr, t_all *all)
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
	free(fr);
	return (-1);
}

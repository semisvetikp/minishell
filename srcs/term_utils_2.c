/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:08:49 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/01 23:08:53 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		up(t_lines **curr_line)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eos, 1, &ft_putchar);
	if ((*curr_line)->prev != NULL)
		*curr_line = (*curr_line)->prev;
	write(1, (*curr_line)->line, ft_strlen((*curr_line)->line));
}

void		down(t_lines **curr_line)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eos, 1, &ft_putchar);
	if ((*curr_line)->next != NULL)
		*curr_line = (*curr_line)->next;
	write(1, (*curr_line)->line, ft_strlen((*curr_line)->line));
}

void		bakcspace(t_lines *curr_line)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eos, 1, &ft_putchar);
	curr_line->line[ft_strlen(curr_line->line) - 1] = '\0';
	write(1, curr_line->line, ft_strlen(curr_line->line));
	tputs(delete_character, 1, &ft_putchar);
}

int			enter(t_lines **curr_line, t_all *all, char *str, char *name)
{
	write(1, &str[0], 1);
	tputs(save_cursor, 1, ft_putchar);
	write_to_bash_history((*curr_line)->line, all);
	t_term_to_cannon(all, name);
	split_line((*curr_line)->line, all);
	return (1);
}

void		els(t_lines **curr_line, char *str)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eos, 1, &ft_putchar);
	((*curr_line)->line = ft_strjoin2((*curr_line)->line, str))
	== NULL ? errm() : 0;
	write(1, (*curr_line)->line, ft_strlen((*curr_line)->line));
}

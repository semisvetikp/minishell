/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:06:17 by dmarget           #+#    #+#             */
/*   Updated: 2021/04/01 23:06:21 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_putchar(int c)
{
	return (write(1, &c, 1));
}

t_lines		*ft_lines_new_empty(void)
{
	t_lines	*line;

	line = (t_lines*)malloc(sizeof(t_lines));
	if (!line)
		return (0);
	line->next = 0;
	line->prev = 0;
	return (line);
}

int			ft_ch_is_in_str(char ch, char const *str)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == ch)
			return (1);
	return (0);
}

void		ft_lines_add_back(t_lines **lst, t_lines *new)
{
	if ((*lst) == 0)
		(*lst) = new;
	else
		ft_lines_add_back(&((*lst)->next), new);
}

void		ft_line_list_clear(t_lines **lst)
{
	t_lines	*temp;
	t_lines	*old;

	temp = *lst;
	while (temp)
	{
		old = temp;
		free(temp->line);
		temp = temp->next;
		free(old);
	}
	*lst = NULL;
}

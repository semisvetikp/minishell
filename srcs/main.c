/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:05:58 by jradioac          #+#    #+#             */
/*   Updated: 2021/03/31 16:37:03 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			cntrl_c(t_lines **curr_line, t_all *all)
{
	if ((*curr_line)->line != NULL)
		ft_strclr((*curr_line)->line);
	write(1, "\n", 1);
	write(1, "minishell$ ", 11);
	tputs(save_cursor, 1, ft_putchar);
	all->g_exit = 1;
}

int				vile(t_lines **curr_line, char *str, t_all *all, char te)
{
	while (1)
	{
		str[0] = '\0';
		all->rb = read(0, str, 2000);
		str[all->rb] = 0;
		if (!ft_strncmp(str, "\e[A", ft_strlen("\e[A")))
			up(&(*curr_line));
		else if (!ft_strncmp(str, "\e[B", ft_strlen("\e[B")))
			down(&(*curr_line));
		else if (!ft_strncmp(str, "\e[C", ft_strlen("\e[C"))
			|| !ft_strncmp(str, "\e[D", ft_strlen("\e[D")))
			continue;
		else if (!ft_strncmp(str, "\177", 1))
			bakcspace(*curr_line);
		else if (ft_strncmp(str, "\n", 1) == 0)
			return (enter(&(*curr_line), all, str, all->name));
		else if (ft_strncmp(str, "\4", 1) == 0 && (*curr_line)->line[0] == '\0')
			exit(write(1, "exit\n", 5));
		else if (ft_strncmp(str, "\3", 3) == 0)
			cntrl_c(&(*curr_line), all);
		else if (ft_strncmp(str, &te, 1) == 0 || ft_strncmp(str, "\t", 1) == 0)
			continue;
		else
			els(&(*curr_line), str);
	}
}

int				termcap(t_lines *curr_line, t_all *all, char *name)
{
	char		str[2000];
	char		te;

	te = 28;
	all->name = name;
	while (1)
		return (vile(&curr_line, str, all, te));
}

void			reading(t_all *all, t_mvar *mvar)
{
	while (mvar->reading != 0)
	{
		tcgetattr(0, &all->term);
		all->term.c_lflag &= ~(ECHO | ICANON | ISIG);
		tcsetattr(0, TCSANOW, &all->term);
		tgetent(0, mvar->term_name);
		ft_line_list_clear(&mvar->line_list_start);
		mvar->st_str = read_bash_history(all);
		mvar->line_list_start = ft_split_to_line_list(mvar->st_str);
		free(mvar->st_str);
		mvar->curr_line = mvar->line_list_start;
		while (mvar->curr_line->next != NULL)
			mvar->curr_line = mvar->curr_line->next;
		write(1, "minishell$ ", 11);
		tputs(save_cursor, 1, ft_putchar);
		mvar->reading = termcap(mvar->curr_line, all, mvar->term_name);
	}
}

int				main(int argc, char **argv, char **envp)
{
	t_all		all;
	t_mvar		mvar;

	init_structure(&all);
	make_environment_variable(&all, envp);
	(void)argc;
	(void)argv;
	mvar.line_list_start = NULL;
	mvar.term_name = "xterm-256color";
	mvar.reading = 1;
	signal(SIGQUIT, sigquit);
	signal(SIGINT, sigint);
	while (1)
		reading(&all, &mvar);
}

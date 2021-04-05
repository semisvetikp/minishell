/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:26:25 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/02 03:08:23 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include "../libft/libft.h"
# include <term.h>
# include <termios.h>
# include <curses.h>

typedef struct		s_replace
{
	int				i;
	int				start;
	int				end;
	int				length;
	char			*key;
	char			*line_copy;
	int				last;
}					t_replace;

typedef struct		s_env
{
	int				id;
	char			*key;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct		s_main
{
	char			**array;
	char			*home;
	char			*path_history;
}					t_main;

typedef struct		s_fd
{
	int				fd0;
	int				fd1;
	int				tmpfd;
	int				pfd[2];
}					t_fd;

typedef struct		s_redir
{
	char			type;
	char			*argwrite;
	char			**create;
	char			**read;
	char			**addwrite;
	char			*argread;
}					t_redir;

typedef struct		s_cd
{
	t_env			*home;
	t_env			*pwd;
	t_env			*oldpwd;
	t_env			*path;
}					t_cd;

typedef struct		s_lines
{
	char			*line;
	struct s_lines	*next;
	struct s_lines	*prev;
}					t_lines;

typedef struct		s_mvar
{
	char			*term_name;
	t_lines			*curr_line;
	t_lines			*line_list_start;
	char			*st_str;
	int				reading;
}					t_mvar;

typedef struct		s_fenv
{
	t_env			*tmp;
	char			*s;
	int				i;
}					t_fenv;

typedef	struct		s_sl
{
	int				i;
	int				start;
	t_lines			*curr_line;
	t_lines			*prev_line;
	t_lines			*lise_list_start;
}					t_sl;

typedef struct		s_all
{
	int				j;
	t_main			main;
	t_env			*env;
	t_cd			*cd;
	int				rb;
	char			*name;
	struct termios	term;
	char			**menv;
	t_fd			fd;
	t_redir			redir;
	int				pip;
	int				g_exit;
}					t_all;

char				*ft_echo(t_all *all, char **arg);
char				*envp(t_all *all, t_env *envp);
char				*ft_export(t_env *env, char **arg, t_all *all);
char				**clear_split(char **array);
int					parser1(char *line, t_all *all);
void				check_equal(t_env *env, char **arg, t_all *all);
void				fill_env(t_env *env, char *envp, t_all *all);
int					search_env(t_env *env, char *arg);
int					check_error(t_all *all, char **arg, char func);
char				*unset(t_all *all, t_env **env, char **arg);
char				*pwd(t_all *all, t_env *env, int flag);
char				*cd(t_env *env, char **arg, t_all *all);
char				*cd_minus(char *str, t_all *all);
char				*cd_path(t_env *env, char *str, t_all *all, char **arg);
int					launch(char **args, t_all *all);
void				ft_exit(t_all *all, int code);
char				**array_env(t_env *env);
char				*choose_path(char *args0, t_all *all, int i);
char				*check_aout(char *args0, t_all *all);
void				make_environment_variable(t_all *all, char **envp);
int					redirect_execve(t_redir redir, t_all *all);
void				ft_error(char *str, t_all *all, char func, char *arg);
int					onlydigit(char *str);
void				init_structure(t_all *all);
char				*choose_cmd(t_all *all, char *line);
void				pars_redirect(char *line, t_all *all);
int					do_pipe(char *line, t_all *all);
int					launch_pipe(char **args, t_all *all);
char				*check_exec(char **args, t_all *all);
void				handling_exit(t_all *all, char **args);
void				free_null_redirect(t_all *all);
char				**array_env(t_env *env);
int					split_line(char *line, t_all *all);
void				coder(char *line, int i, int slash);
void				decoder(char *line);
int					check_line(char *line, t_all *all);
int					valid_line(char *line, t_all *all);
int					valid_pipe(char *line, t_all *all);
int					get_space_count(char *line);
int					spec_syntax_error(char *error, char *fr, t_all *all);
void				squeeze (char *s, int c);
int					syntax_error(char *error, t_all *all);
char				**split_arg(char *line, char c);
int					count_same_chr(char *line, int i, char c, int dir);
int					count_c(char *line, int c);
int					valid_bracket(char *line, t_all *all);
int					is_escape(char *line, int i);
int					valid_slash(char *line, t_all *all);
int					valid_arg(char *line, int c1, int c2);
int					check_dquotes(char *line, int i, t_all *all);
int					check_quotes(char *line, int i, t_all *all);
int					check_empty_line(char *line);
void				check_escape(char *line);
char				*replace_env(char *line, t_all *all);
int					valid_redir(char *line, t_all *all);
void				check_last_write_redirect(char *line, t_all *all);
char				*pars_check_redir(char *line, t_all *all);
int					count_redir(char *line);
int					split_pipe(char *line, t_all *all);
int					ft_putchar(int c);
t_lines				*ft_lines_new_empty();
int					ft_ch_is_in_str(char ch, char const *str);
void				ft_lines_add_back(t_lines **lst, t_lines *new);
void				ft_line_list_clear(t_lines **lst);
char				*read_bash_history(t_all *all);
int					write_to_bash_history(char *str, t_all *all);
void				sigint(int sig);
void				sigquit(int sig);
int					errm(void);
void				help_remind_cd_home(t_env *tmp, int i, t_all *all, char *s);
void				help_remind_cd_path(t_env *tmp, int i, t_all *all, char *s);
void				remind_cd(t_all *all, char *s, t_env *tmp, int i);
t_lines				*ft_split_to_line_list(char *str);
void				t_term_to_cannon(t_all *all, char *name);
void				down(t_lines **curr_line);
void				bakcspace(t_lines *curr_line);
int					enter(t_lines **curr_line, t_all *all,
							char *str, char *name);
void				up(t_lines **curr_line);
void				els(t_lines **curr_line, char *str);
int					c_redir(char *line);
int					valid_semicolon(char *line, t_all *all);
char				*parse_redir(char *line, t_all *all, int last, char c);
t_env				*ft_envnew(void);
int					ft_envsize(t_env *env);
t_env				*ft_envlast(t_env *env);
t_env				*ft_envadd_back(t_env **env, t_env *new);
void				ft_envdelone(t_env **env, t_env *tmp, t_env *pr);
char				**sort_env(t_env *env, int i);
char				*free_null(char *str);

#endif

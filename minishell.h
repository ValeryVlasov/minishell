/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 20:28:46 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/14 17:59:29 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "gnl/get_next_line.h"
# define BUFF_SIZE 4096

# define STDIN 0
# define STDOUT 1
# define STDERR 2

//для сигналов
extern int	g_last_exit_code;
extern int	rl_catch_signals;
# define PROMPT "☣ minishell ▸:"
# define PROMPT_ERR "Minishell:"

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_word
{
	char			*content;
	int				special;
	int				is_pipe;
	int				redir_out;
	int				redir_input;
	int				heredoc;
	int				append;
	struct s_word	*next;
}				t_word;

typedef struct s_mshell
{
	char			**cmds;
	int				is_path;
	int				list_size;
	int				cmd_size;
	struct s_env	*hidden;
	struct s_env	*head_env;
	struct s_cmd	*head_cmd;
	struct s_word	*head_word;
	sig_t			sigint;
	sig_t			sigquit;
}				t_mini;

typedef struct s_heredoc
{
	char		*stop_word;
	char		*content;
}				t_heredoc;

typedef struct s_cmd
{
	char			**cmds;
	char			*path_with_name;
	int				pipe_fd[2];
	int				fd_input;
	int				fd_out;
	int				redir_out;
	int				redir_in;
	int				builtin;
	int				pid;
	int				heredoc;
	int				to_remove;
	struct s_cmd	*next;
}				t_cmd;

int		is_valid(char *arg);
int		parsing(char *line, t_mini *main);
//mem_delete.c
void	*delete_mem(void *ptr);
void	*free_strarr(char **arr);

//env.c
char	**copy_env(t_env *env);
int		env_size(const t_env *env);
char	*get_env_name(char *src);
char	*get_env_val(char *name, t_env *env);
char	*find_env(t_env *envp, char *to_find);

//utils.c
t_env	*add_last(t_env *hidden, char *arg);
int		ft_access(char *path);
int		env_size(const t_env *env);

//heredoc.c
int		here_doc_handle(t_mini *mshell, t_cmd *curr, char *stop_word);

//shell_lvl.c
void	inc_shlvl(t_env *env);

void	delete_list_cmd(t_cmd *list);

//checks.c
void	check_pipe_or_cmd(t_mini *mshell);
void	dup_redirs(t_cmd *cmd);

//file.c
int		change_fd(t_mini *mshell, t_cmd *cmd, int i, int is_out);
char	*get_path_cmd(t_env *envp, char *command);

//cmd_init.c
t_cmd	*init_s_cmd(int count);

int		is_in_env(char *name, t_env *env);
void	add_env(t_env *env, char *data);

//handling_main_cmd.c
void	handling_cmds(t_mini *mshell, int cnt_cmd);
//handling_cmd_utils.c
char	**resize_cmd(t_cmd *cmd);
t_word	*jump_pipe(t_word *word, int index_cmd, int *i);

//counting.c
int		count_bin(t_env *env, t_cmd *cmd_list);
int		count_pipes(t_word *word);
int		count_args(char **args);
int		matrix_size(char **matrix);
int		size_cmd(t_word *word, int count);

//bin.c
int		bin_exec(t_mini *mshell, t_cmd *cur_cmd);
int		is_bin(t_env *env, char *cmd);
//builtins/
int		is_builtin(char *cmd);
int		builtin_exec(t_mini *mshell, t_cmd *cur_cmd);
//cd.c
void	ft_cd(t_mini *mshell, char **cmd, int argc);
t_env	*get_key(t_env *env, char *to_find);
//echo.c
void	ft_echo(char **cmd, int argc);
//unset.c
void	ft_unset(t_mini *mshell, t_cmd *cmd);
//pwd.c
void	ft_pwd(void);
//export.c
void	ft_export(t_mini *mshell, char **args);
t_env	*find_key(t_env *src, char *to_find);
void	print_sort_env(t_env *env);
//exit.c
void	ft_exit(char **cmd, int argc);
//env.c
void	ft_env(t_env *env);

//errors.c
void	print_error(char *prog, char *arg);
void	print_err(char *cmd, char *arg, char *msg);
int		pipe_err(void);
int		fork_err(void);
void	mem_err(void);

//парсер функции
char	**first_trim_line(char *line, char *set);
char	*element_trim_line(char *line, char *set);
char	**expand_path(char **set, t_mini *main);
void	ft_delete_quotes(t_mini *head);
int		minishell_heredoc(t_heredoc *data);
int		error_quotes(int count_pip);
void	delete_list_word(t_word *list);
void	parsing_word(char **cmd, t_mini *mini);
int		syntax_error(char *line);
int		find_syntax_word(t_mini *main);
int		ft_free_str_error(char *line);
char	*help_path(char *find_str);
//работа со структурой env
t_env	*init_env(char **envp);
void	delete_env(t_env *list);
t_env	*new_node_env(char *data);
//раббота со структурой  mshell
t_mini	*init_struct_mini(char **env);
//раббота со структурой  cmd
void	parsing_cmd(char **cmd, t_mini *mini);
t_cmd	*push_cmd(t_cmd *head, char *data);
t_cmd	*init_stuct_cmd(char *data);
//сигналы
void	rl_replace_line(const char *str, int a);
void	ctl_c_handle(int x);
void	handle_sigs(int argc, t_mini *main);
void	new_line(int x);
void	handle_child(char *cmd);
void	handle_sigquit(int sig);
#endif

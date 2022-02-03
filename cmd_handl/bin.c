/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:57:29 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/14 17:52:28 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_bin(t_env *env, char *cmd)
{
	char	*path;

	path = get_path_cmd(env, cmd);
	if (path)
	{
		delete_mem(path);
		return (1);
	}
	return (0);
}

static void	check_directory(char *name)
{
	int	fd;

	if (!name || !name[0])
		return ;
	if (name[0] && name[1] && name[0] == name[1] && name[0] == '.')
		return ;
	fd = open(name, O_WRONLY);
	if (errno == EISDIR)
		g_last_exit_code = 126;
	if (fd > 0)
		close(fd);
}

static void	is_dir_msg(char *cmd)
{
	if (errno == EISDIR)
		print_error(cmd, NULL);
	else
		print_err(cmd, NULL, "command not found\n");
}

int	bin_exec(t_mini *mshell, t_cmd *cur_cmd)
{
	char	**envp;

	if (pipe(cur_cmd->pipe_fd) == -1)
		return (pipe_err());
	cur_cmd->pid = fork();
	if (cur_cmd->pid == -1)
		return (fork_err());
	if (cur_cmd->pid != 0)
		handle_child(cur_cmd->cmds[0]);
	if (cur_cmd->pid == 0)
	{
		rl_catch_signals = 0;
		signal(SIGINT, mshell->sigint);
		signal(SIGQUIT, mshell->sigquit);
		dup_redirs(cur_cmd);
		envp = copy_env(mshell->head_env);
		if (cur_cmd->path_with_name)
			execve(cur_cmd->path_with_name, cur_cmd->cmds, envp);
		free_strarr(envp);
		check_directory(cur_cmd->path_with_name);
		is_dir_msg(cur_cmd->cmds[0]);
		exit(1);
	}
	close(cur_cmd->pipe_fd[1]);
	return (cur_cmd->pipe_fd[0]);
}

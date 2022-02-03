/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:17:44 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:17:50 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

static void	choose_builtin(t_mini *mshell, t_cmd *cmd)
{
	g_last_exit_code = 0;
	if (ft_strcmp(cmd->cmds[0], "cd") == 0)
		ft_cd(mshell, cmd->cmds, matrix_size(cmd->cmds));
	else if (ft_strcmp(cmd->cmds[0], "echo") == 0)
		ft_echo(cmd->cmds, matrix_size(cmd->cmds));
	else if (ft_strcmp(cmd->cmds[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmds[0], "export") == 0)
		ft_export(mshell, cmd->cmds);
	else if (ft_strcmp(cmd->cmds[0], "exit") == 0)
		ft_exit(cmd->cmds, matrix_size(cmd->cmds));
	else if (ft_strcmp(cmd->cmds[0], "env") == 0)
		ft_env(mshell->head_env);
	else if (ft_strcmp(cmd->cmds[0], "unset") == 0)
		ft_unset(mshell, cmd);
	else
		g_last_exit_code = 127;
}

int	builtin_exec(t_mini *mshell, t_cmd *cur_cmd)
{
	int		save_in;
	int		save_out;

	if (pipe(cur_cmd->pipe_fd) == -1)
		return (pipe_err());
	save_in = dup(STDIN_FILENO);
	if (save_in == -1)
		return (pipe_err());
	save_out = dup(STDOUT_FILENO);
	if (save_out == -1)
		return (pipe_err());
	dup_redirs(cur_cmd);
	choose_builtin(mshell, cur_cmd);
	if (cur_cmd->redir_in > 0)
	{
		close(cur_cmd->redir_in);
		cur_cmd->redir_in = -1;
	}
	dup2(save_out, STDOUT_FILENO);
	close(save_out);
	dup2(save_in, STDIN_FILENO);
	close(save_in);
	return (cur_cmd->pipe_fd[0]);
}

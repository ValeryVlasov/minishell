/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:52:25 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/12 14:16:06 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_redirs(t_cmd *cmd)
{
	if (cmd->redir_out != -2)
		dup2(cmd->redir_out, STDOUT_FILENO);
	if (cmd->redir_in != -2)
		dup2(cmd->redir_in, STDIN_FILENO);
	if (cmd->redir_out < 0 && cmd->next)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close(cmd->pipe_fd[1]);
	if (!cmd->builtin)
		close(cmd->pipe_fd[0]);
}

static void	parent_handling(t_mini *mshell)
{
	int		status;
	t_cmd	*temp;

	status = 0;
	temp = mshell->head_cmd;
	while (temp)
	{
		if (temp->pid != -1 && temp->pid != -2)
		{
			if (temp->pipe_fd[0] != -1)
				close(temp->pipe_fd[0]);
			waitpid(temp->pid, &status, 0);
		}
		if (temp->builtin && temp->pipe_fd[0] != -1)
		{
			close(temp->pipe_fd[0]);
			temp->pipe_fd[0] = -1;
		}
		if (temp->pid == -1)
			g_last_exit_code = 1;
		temp = temp->next;
	}
}

static void	close_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe_fd[0] != -1)
		{
			close(cmd->pipe_fd[0]);
			cmd->pipe_fd[0] = -1;
		}
		cmd = cmd->next;
	}
}

static void	my_exec(t_mini *mshell)
{
	int		is_last_cmd;
	t_cmd	*temp;

	if (!mshell->head_cmd || !mshell->head_cmd->cmds)
		return ;
	is_last_cmd = -1;
	temp = mshell->head_cmd;
	while (temp)
	{
		if (temp->redir_in == -2 && is_last_cmd != -1)
			temp->redir_in = is_last_cmd;
		if (temp->builtin)
			is_last_cmd = builtin_exec(mshell, temp);
		else
			is_last_cmd = bin_exec(mshell, temp);
		if (is_last_cmd == -1)
			break ;
		temp = temp->next;
	}
	if (is_last_cmd != -1)
		close_pipes(mshell->head_cmd);
	parent_handling(mshell);
}

void	check_pipe_or_cmd(t_mini *mshell)
{
	mshell->cmd_size = count_pipes(mshell->head_word) + 1;
	handling_cmds(mshell, mshell->cmd_size);
	my_exec(mshell);
}

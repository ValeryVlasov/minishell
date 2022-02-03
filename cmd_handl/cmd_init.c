/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:51:39 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:23:18 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_list_cmd(t_cmd *list)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = list;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->cmds)
			delete_mem(tmp->path_with_name);
		free_strarr(tmp->cmds);
		delete_mem(tmp);
		tmp = next;
	}
}

t_cmd	*new_node(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmds = NULL;
	cmd->next = NULL;
	cmd->path_with_name = NULL;
	cmd->fd_input = STDIN;
	cmd->fd_out = STDOUT;
	cmd->redir_out = -2;
	cmd->redir_in = -2;
	cmd->builtin = 0;
	cmd->pid = -2;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->heredoc = 0;
	cmd->to_remove = 0;
	return (cmd);
}

t_cmd	*init_s_cmd(int count)
{
	t_cmd	*cmd;
	t_cmd	*temp;
	int		i;

	i = 0;
	cmd = new_node();
	if (!cmd)
		mem_err();
	if (count == 1)
		return (cmd);
	temp = cmd;
	while (i < count - 1)
	{
		cmd->next = new_node();
		if (!cmd->next)
			mem_err();
		cmd = cmd->next;
		i++;
	}
	return (temp);
}

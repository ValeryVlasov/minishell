/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_main_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:44:08 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/14 17:53:27 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_on_redir(t_mini *mshell, t_cmd *cur_cmd)
{
	int		i;
	int		is_failed;

	i = 0;
	is_failed = 0;
	while (cur_cmd->cmds[i])
	{
		if (ft_strcmp(cur_cmd->cmds[i], "<") == 0 && cur_cmd->cmds[i + 1])
			is_failed = change_fd(mshell, cur_cmd, ++i, 0);
		else if (ft_strcmp(cur_cmd->cmds[i], ">") == 0 && cur_cmd->cmds[i + 1])
			is_failed = change_fd(mshell, cur_cmd, ++i, 1);
		else if (ft_strcmp(cur_cmd->cmds[i], ">>") == 0 && cur_cmd->cmds[i + 1])
			is_failed = change_fd(mshell, cur_cmd, ++i, 2);
		else if (ft_strcmp(cur_cmd->cmds[i], "<<") == 0 && cur_cmd->cmds[i + 1])
			is_failed = here_doc_handle(mshell, cur_cmd, cur_cmd->cmds[++i]);
		if (is_failed)
			break ;
		i++;
	}
	cur_cmd->cmds = resize_cmd(cur_cmd);
	return (is_failed);
}

static t_cmd	*handle_cur_cmd(t_mini *mshell, t_cmd *cmd, int index_cmd)
{
	int		i;
	int		j;
	t_word	*temp;

	temp = jump_pipe(mshell->head_word, index_cmd, &i);
	if (!cmd)
		return (NULL);
	j = size_cmd(mshell->head_word, i) + 1;
	cmd->cmds = (char **)malloc(sizeof(char *) * j);
	if (!cmd->cmds)
		return (NULL);
	j = 0;
	while (temp)
	{
		if (ft_strcmp(temp->content, "|") == 0 && temp->special == 1)
			break ;
		cmd->cmds[j++] = ft_strdup(temp->content);
		temp = temp->next;
	}
	cmd->cmds[j] = NULL;
	cmd->to_remove = check_on_redir(mshell, cmd);
	if (!cmd->cmds || !cmd->cmds[0])
		return (cmd);
	cmd->path_with_name = get_path_cmd(mshell->head_env, cmd->cmds[0]);
	return (cmd);
}

void	*delete_node(t_cmd *node)
{
	node->next = NULL;
	if (node->cmds && node->cmds[0])
		delete_mem(node->path_with_name);
	free_strarr(node->cmds);
	delete_mem(node);
	return (NULL);
}

static t_cmd	*remove_failed(t_cmd *cmd)
{
	t_cmd	*temp;
	t_cmd	*save;

	temp = cmd;
	while (temp)
	{
		save = temp;
		temp = temp->next;
		if (temp && temp->to_remove)
		{
			save->next = temp->next;
			delete_node(temp);
		}
	}
	if (cmd->to_remove)
	{
		temp = cmd->next;
		delete_node(cmd);
		cmd = temp;
	}
	return (cmd);
}

void	handling_cmds(t_mini *mshell, int cnt_cmd)
{
	int		temp;
	t_cmd	*m_cmd;
	int		count;
	t_word	*save;

	temp = cnt_cmd;
	m_cmd = init_s_cmd(cnt_cmd);
	mshell->head_cmd = m_cmd;
	count = -1;
	save = mshell->head_word;
	while (cnt_cmd-- > 0)
	{
		count++;
		if (save && ft_strcmp(save->content, "|") == 0)
			save = save->next;
		m_cmd = handle_cur_cmd(mshell, m_cmd, temp - cnt_cmd - 1);
		if (!m_cmd->cmds)
			break ;
		m_cmd->builtin = is_builtin(m_cmd->cmds[0]);
		m_cmd = m_cmd->next;
		save = save->next;
	}
	mshell->head_cmd = remove_failed(mshell->head_cmd);
}

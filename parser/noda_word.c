/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noda_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:02:13 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/12 14:49:39 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_list_word(t_word *list)
{
	t_word	*tmp;
	t_word	*next;

	tmp = list;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		delete_mem(tmp->content);
		delete_mem(tmp);
		tmp = next;
	}
}

static t_word	*init_flag(t_word *cmd)
{
	cmd->special = 0;
	cmd->append = 0;
	cmd->redir_out = 0;
	cmd->redir_input = 0;
	cmd->heredoc = 0;
	cmd->is_pipe = 0;
	return (cmd);
}

static t_word	*my_is_flag(t_word *cmd, char *data)
{
	if (ft_strchr(">|<", data[0]))
	{
		cmd->special = 1;
		if (data[0] == '|')
			cmd->is_pipe = 1;
		else if (data[0] == '>' && data[1] == '>')
			cmd->append = 1;
		else if (data[0] == '<' && data[1] == '<')
			cmd->heredoc = 1;
		else if (data[0] == '<')
			cmd->redir_input = 1;
		else if (data[0] == '>')
			cmd->redir_out = 1;
		return (cmd);
	}
	cmd->special = 0;
	return (cmd);
}

t_word	*push_word(char *data)
{
	t_word	*temp;

	temp = (t_word *)malloc(sizeof(t_word));
	if (!temp)
		return (NULL);
	temp->content = ft_strdup(data);
	temp->next = NULL;
	temp = init_flag(temp);
	temp = my_is_flag(temp, data);
	return (temp);
}

void	parsing_word(char **cmd, t_mini *mini)
{
	t_word	*new_word;
	int		i;

	i = 1;
	if (!cmd)
		return ;
	new_word = push_word(cmd[0]);
	mini->head_word = new_word;
	while (cmd[i])
	{
		new_word->next = push_word(cmd[i]);
		new_word = new_word->next;
		i++;
	}
}

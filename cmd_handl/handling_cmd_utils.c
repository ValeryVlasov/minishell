/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:08:52 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/14 22:46:22 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_word	*jump_pipe(t_word *word, int index_cmd, int *i)
{
	int		cnt_pipe;

	cnt_pipe = 0;
	(*i) = 0;
	while (word && word->content && cnt_pipe != index_cmd)
	{
		if (ft_strcmp(word->content, "|") == 0 && word->special == 1)
			cnt_pipe++;
		word = word->next;
		(*i)++;
	}
	if (!word || !word->content)
		return (NULL);
	return (word);
}

static int	len_wo_redirs(char **cmds)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (cmds[++i])
	{
		if (ft_strcmp(cmds[i], "<") == 0
			|| ft_strcmp(cmds[i], ">") == 0
			|| ft_strcmp(cmds[i], ">>") == 0
			|| ft_strcmp(cmds[i], "<<") == 0)
			len -= 2;
		len++;
	}
	return (len);
}

void	*resize_free(char **cmd)
{
	free_strarr(cmd);
	return (NULL);
}

char	**resize_cmd(t_cmd *cmd)
{
	char	**replace;
	int		i;
	int		j;

	j = len_wo_redirs(cmd->cmds);
	if (j == 0)
		return (resize_free(cmd->cmds));
	replace = (char **)malloc(sizeof(char *) * (j + 1));
	if (!replace)
		return (free_strarr(cmd->cmds));
	replace[j] = NULL;
	i = -1;
	j = 0;
	while (cmd->cmds && cmd->cmds[++i])
	{
		if (ft_strcmp(cmd->cmds[i], "<") == 0
			|| ft_strcmp(cmd->cmds[i], ">") == 0
			|| ft_strcmp(cmd->cmds[i], ">>") == 0
			|| ft_strcmp(cmd->cmds[i], "<<") == 0)
			i++;
		else
			replace[j++] = ft_strdup(cmd->cmds[i]);
	}
	free_strarr(cmd->cmds);
	return (replace);
}

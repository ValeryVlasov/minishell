/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:49:10 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:23:35 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_bin(t_env *env, t_cmd *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list)
	{
		if (is_bin(env, cmd_list->cmds[0]))
			count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

int	count_pipes(t_word *word)
{
	int		count;
	t_word	*temp;

	count = 0;
	temp = word;
	while (temp)
	{
		if (ft_strcmp(temp->content, "|") == 0 && temp->special == 1)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	matrix_size(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	size_cmd(t_word *word, int count)
{
	while (count > 0)
	{
		word = word->next;
		count--;
	}
	while (word)
	{
		if (ft_strcmp(word->content, "|") == 0 && word->special == 1)
			break ;
		word = word->next;
		count++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:52:41 by aizetta           #+#    #+#             */
/*   Updated: 2022/01/12 14:51:30 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_last_exit_code = 0;

int	is_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i])
		return (0);
	return (1);
}

void	free_loop_2(t_mini *mshell)
{
	if (mshell->cmds)
		free_strarr(mshell->cmds);
	delete_list_cmd(mshell->head_cmd);
	delete_list_word(mshell->head_word);
}

int	parsing(char *line, t_mini *main)
{
	char	**set;

	if (line && is_space(line))
		return (1);
	if (line && line[0])
	{
		line = element_trim_line(line, "|<>");
		if (line == NULL || syntax_error(line) == -1)
			return (ft_free_str_error(line));
		set = first_trim_line(line, " ");
		set = expand_path(set, main);
		parsing_word(set, main);
		if (find_syntax_word(main))
		{
			free_loop_2(main);
			free_strarr(set);
			return (1);
		}
		ft_delete_quotes(main);
		free_strarr(set);
		return (0);
	}
	else
		return (1);
}

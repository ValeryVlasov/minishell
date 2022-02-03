/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:51:34 by aizetta           #+#    #+#             */
/*   Updated: 2022/01/09 15:59:57 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_quotes(const char *line, int i[5])
{
	while (line && line[i[2]])
	{
		i[4] = (i[4] + (!i[3] && line[i[2]] == '\'')) % 2;
		i[3] = (i[3] + (!i[4] && line[i[2]] == '\"')) % 2;
		if ((line[i[2]] == '\"' && !i[4]) || (line[i[2]] == '\'' && !i[3]))
			i[1]++;
		i[2]++;
	}
	if (i[4] || i[3])
		return (-1);
	i[1] = ft_strlen(line) - i[1] + 1;
	return (i[1]);
}

static char	*array_new_line_no_quotes(char *old_line, char *new_line, int i[5])
{
	while (old_line[i[2]])
	{
		i[4] = (i[4] + (!i[3] && old_line[i[2]] == '\'')) % 2;
		i[3] = (i[3] + (!i[4] && old_line[i[2]] == '\"')) % 2;
		if ((old_line[i[2]] != '\"' || i[4]) && (old_line[i[2]] != '\''
				||i[3]) && ++i[1] >= 0)
			new_line[i[1]] = old_line[i[2]];
		i[2]++;
	}
	new_line[++i[1]] = '\0';
	delete_mem(old_line);
	return (new_line);
}

void	ft_delete_quotes(t_mini *head)
{
	char	*new_line;
	int		count[5];
	t_word	*p;

	p = head->head_word;
	count[0] = 0;
	while (p)
	{
		count[1] = 0;
		count[2] = 0;
		count[3] = 0;
		count[4] = 0;
		new_line = malloc(ft_count_quotes(p->content, count) * sizeof(char));
		if (new_line == NULL)
			return ;
		count[1] = -1;
		count[2] = 0;
		count[3] = 0;
		count[4] = 0;
		p->content = array_new_line_no_quotes(p->content, new_line,
				count);
		p = p->next;
	}
}

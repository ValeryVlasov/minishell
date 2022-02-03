/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:23:55 by aizetta           #+#    #+#             */
/*   Updated: 2022/01/15 18:56:29 by aizetta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(t_mini *main, char *line, int start, int end)
{
	char	*find_str;
	int		j;
	t_env	*head;

	head = main->head_env;
	find_str = ft_substr(line, start, end - start);
	if (find_str[0] == '?')
		return (help_path(find_str));
	while (head)
	{
		j = 0;
		while (head->str[j] && find_str[j] && head->str[j] == find_str[j])
		{
			if (head->str[j + 1] == '=' && !find_str[j + 1])
			{
				delete_mem(find_str);
				return (ft_substr(head->str, j + 2, ft_strlen(head->str)));
			}
			j++;
		}
		head = head->next;
	}
	delete_mem(find_str);
	return (NULL);
}

static char	*expand_new_path(char *path, char *line, int i[5])
{
	char	*buffer;
	char	*new_line;

	i[2]--;
	buffer = ft_substr(line, 0, i[2]);
	new_line = ft_strjoin(buffer, path);
	delete_mem(path);
	delete_mem(buffer);
	buffer = ft_substr(line, i[1] + 1, ft_strlen(line) - i[1]);
	delete_mem(line);
	line = ft_strjoin(new_line, buffer);
	delete_mem(buffer);
	delete_mem(new_line);
	return (line);
}

static int	quote_flag(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\"')
			return (2);
		if (line[i] == '\'')
			return (1);
		i++;
	}
	return (1);
}

static char	*new_malloc_len(char *line, int i[5], t_mini *main)
{
	char	*new_path;
	int		flag;

	flag = quote_flag(line);
	while (line && i[1] < ft_strlen(line))
	{
		i[3] = (i[3] + (!i[4] && line[i[1]] == '\'')) % 2;
		i[4] = (i[4] + (!i[3] && line[i[1]] == '\"')) % 2;
		if ((i[4] || (!i[3] && !i[4]) || (i[3] && i[4] && flag == 2))
			&& (line[i[1]] == '$' && line[i[1] + 1]))
		{
			i[2] = i[1] + 1;
			i[1]++;
			while (line[i[1]] && !ft_strchr("/~%^{}:;\"\' $", line[i[1]]))
				i[1]++;
			new_path = find_path(main, line, i[2], i[1]);
			line = expand_new_path(new_path, line, i);
		}
		i[1]++;
	}
	return (line);
}

char	**expand_path(char **set, t_mini *main)
{
	int		count[5];

	count[0] = 0;
	if (!set || !set[count[0]])
		return (NULL);
	while (set[count[0]])
	{
		count[1] = 0;
		count[2] = 0;
		count[3] = 0;
		count[4] = 0;
		set[count[0]] = new_malloc_len(set[count[0]], count, main);
		count[0]++;
	}
	return (set);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_trim_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:52:07 by aizetta           #+#    #+#             */
/*   Updated: 2022/01/02 14:52:11 by aizetta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(const char *str, char *c, int i[5])
{
	while (str[i[0]] != '\0')
	{
		if (!ft_strchr(c, str[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, str[i[0]]) || i[3]) && str[i[0]] != '\0')
			{
				if (!i[4] && (str[i[0]] == '\"' || str[i[0]] == '\''))
					i[4] = str[i[0]];
				i[3] = (i[3] + (str[i[0]] == i[4])) % 2;
				i[4] *= i[3] != 0;
				i[0]++;
			}
			if (i[3])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**array_set(char **new_set, char const *str, char *set, int i[5])
{
	int		str_len;

	i[3] = 0;
	i[4] = 0;
	str_len = ft_strlen(str);
	while (str[i[0]])
	{
		while (ft_strchr(set, str[i[0]]) && str[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, str[i[0]]) || i[3] || i[4]) && str[i[0]])
		{
			i[3] = (i[3] + (!i[4] && str[i[0]] == '\'')) % 2;
			i[4] = (i[4] + (!i[3] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= str_len)
			new_set[i[2]++] = NULL;
		else
			new_set[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (new_set);
}

char	**first_trim_line(char *line, char *set)
{
	int		counts[5];
	char	**new_set;
	int		counts_words;

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	counts[3] = 0;
	counts[4] = 0;
	if (!line)
		return (NULL);
	counts_words = count_words(line, set, counts);
	if (counts_words == -1)
		return (NULL);
	new_set = malloc((counts_words + 1) * sizeof(char *));
	if (new_set == NULL)
		return (NULL);
	counts[0] = 0;
	counts[1] = 0;
	new_set = array_set(new_set, line, set, counts);
	new_set[counts_words] = NULL;
	delete_mem(line);
	return (new_set);
}

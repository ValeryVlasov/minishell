/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_trim_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:51:49 by aizetta           #+#    #+#             */
/*   Updated: 2022/01/12 14:48:24 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_char_pip(const char *str, char *c, int i[5])
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

static int	ft_add_new_str(char *old_str, char *new_str, int i[5], int
start_new)
{
	new_str[start_new] = ' ';
	start_new++;
	new_str[start_new] = old_str[i[1]];
	i[1]++;
	start_new++;
	new_str[start_new] = old_str[i[1]];
	i[1]++;
	start_new++;
	new_str[start_new] = ' ';
	start_new++;
	i[0]++;
	return (start_new);
}

static int	ft_new_copystr(char *old_str, char *new_str, int i[5], int
start_new)
{
	if (ft_strchr(">", old_str[i[1]]) && ft_strchr(">", old_str[i[1] + 1]))
		start_new = ft_add_new_str(old_str, new_str, i, start_new);
	else if (ft_strchr("<", old_str[i[1]]) && ft_strchr("<", old_str[i[1] + 1]))
		start_new = ft_add_new_str(old_str, new_str, i, start_new);
	else if (ft_strchr("|<>", old_str[i[1]]))
	{
		new_str[start_new] = ' ';
		start_new++;
		new_str[start_new] = old_str[i[1]];
		i[1]++;
		start_new++;
		new_str[start_new] = ' ';
		start_new++;
	}
	i[2] = i[0] - i[1];
	while (i[2])
	{
		new_str[start_new] = old_str[i[1]];
		i[1]++;
		start_new++;
		i[2]--;
	}
	return (start_new);
}

static char	*array_new_line(char *new_line, char *str, char *set, int
i[5])
{
	int	len;

	len = 0;
	while (str && str[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, str[i[0]]))
		{
			while ((!ft_strchr(set, str[i[0]]) || i[3] || i[4])
				&& str[i[0]])
			{
				i[3] = (i[3] + (!i[4] && str[i[0]] == '\'')) % 2;
				i[4] = (i[4] + (!i[3] && str[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		len = ft_new_copystr(str, new_line, i, len);
	}
	new_line[len] = '\0';
	return (new_line);
}

char	*element_trim_line(char *line, char *set)
{
	int		counts[5];
	int		count_pip;
	char	*new_line;

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	counts[3] = 0;
	counts[4] = 0;
	if (!line)
		return (NULL);
	count_pip = count_char_pip(line, set, counts);
	if (error_quotes(count_pip))
		return (NULL);
	new_line = malloc(((count_pip * 2) + ft_strlen(line) + 1) * sizeof(char));
	if (new_line == NULL)
		return (NULL);
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	counts[3] = 0;
	counts[4] = 0;
	new_line = array_new_line(new_line, line, set, counts);
	return (new_line);
}

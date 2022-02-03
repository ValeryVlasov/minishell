/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:05:09 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/14 17:59:53 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_quotes(int count_pip)
{
	if (count_pip == -1)
	{
		printf("Minishell: error while looking for matching quote\n");
		g_last_exit_code = 258;
		return (1);
	}
	return (0);
}

int	ft_free_str_error(char *line)
{
	delete_mem(line);
	return (1);
}

int	syntax_error(char *line)
{
	char	*new_line;
	int		i[5];

	new_line = ft_strtrim(line, " ");
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	i[4] = 0;
	while (line && line[i[1]])
	{
		i[3] = (i[3] + (!i[4] && line[i[1]] == '\'')) % 2;
		i[4] = (i[4] + (!i[3] && line[i[1]] == '\"')) % 2;
		if (ft_strchr("~%^{};\\", line[i[1]]) && (!i[3] && !i[4]))
		{
			printf("Minishell: syntax error you use ~{};\\\n");
			g_last_exit_code = 258;
			delete_mem(new_line);
			return (-1);
		}
		i[1]++;
	}
	delete_mem(new_line);
	return (0);
}

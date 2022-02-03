/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:18:13 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:18:34 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_flag(char *flag_str)
{
	int	i;

	i = 0;
	while (flag_str[i])
	{
		if (flag_str[i] != '-' && i == 0)
			return (0);
		if (flag_str[i] != 'n' && i != 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **cmd, int argc)
{
	int	i;
	int	n_flag;

	g_last_exit_code = 0;
	n_flag = 0;
	i = 1;
	if (argc > 1)
	{
		if (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
			n_flag = check_flag(cmd[i]);
		if (n_flag != 0)
			i++;
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (n_flag == 0)
		write(1, "\n", 1);
}

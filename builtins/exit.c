/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:19:05 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:19:25 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **cmd, int argc)
{
	int	i;

	if (argc > 2)
	{
		ft_putstr_fd("exit\n", 2);
		print_err(cmd[0], cmd[1], "too many arguments\n");
		g_last_exit_code = 1;
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		i = 0;
		while (argc > 1 && cmd[1][i] >= '0' && cmd[1][i] <= '9')
			i++;
		if (argc > 1 && cmd[1][i])
		{
			print_err(cmd[0], cmd[1], "numeric argument required\n");
			g_last_exit_code = 255;
		}
		if (argc > 1 && g_last_exit_code != 255)
			g_last_exit_code = ft_atoi(cmd[1]);
		else if (argc == 1)
			g_last_exit_code = 0;
		exit(g_last_exit_code);
	}
}

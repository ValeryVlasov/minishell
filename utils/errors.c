/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:41:04 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:24:19 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_err(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("Minishell: ", 2);
	if (cmd && cmd[0])
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		if (!arg[0])
			ft_putstr_fd("`': ", 2);
		if (arg[0])
			ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	g_last_exit_code = 1;
}

int	fork_err(void)
{
	perror("Minishell: fork");
	return (-1);
}

void	print_error(char *prog, char *arg)
{
	if (!prog && !arg)
		perror("Minishell");
	else
	{
		write(2, "Minishell: ", 11);
		if (prog && arg)
		{
			ft_putstr_fd(prog, 2);
			ft_putstr_fd(": ", 2);
			perror(arg);
		}
		if (!arg)
			perror(prog);
		if (!prog)
			perror(arg);
	}
	g_last_exit_code = 1;
}

void	mem_err(void)
{
	print_error(NULL, NULL);
	exit(1);
}

int	pipe_err(void)
{
	print_error(NULL, NULL);
	return (-1);
}

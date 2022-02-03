/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:25:58 by aizetta           #+#    #+#             */
/*   Updated: 2022/01/12 14:52:23 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctl_c_handle(int x)
{
	if (x == SIGINT)
	{
		(void )x;
		write(1, "  \n", 3);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_last_exit_code = 1;
	}
}

void	new_line(int x)
{
	g_last_exit_code = 128 + x;
	ft_putstr_fd("\n", 1);
}

void	handle_child(char *cmd)
{
	if (cmd)
	{
		if (!ft_strcmp("./minishell", cmd))
			signal(SIGINT, SIG_IGN);
		else
			signal(SIGINT, new_line);
	}
}

void	handle_sigs(int argc, t_mini *main)
{
	(void)argc;
	rl_catch_signals = 0;
	main->sigint = signal(SIGINT, ctl_c_handle);
	main->sigquit = signal(SIGQUIT, SIG_IGN);
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}

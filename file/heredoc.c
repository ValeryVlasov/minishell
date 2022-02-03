/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:53:33 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/14 17:53:40 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	foo(int x)
{
	(void)x;
	ft_putstr_fd("\n", 1);
	rl_catch_signals = 1;
	exit(1);
}

static void	readline_heredoc(char *stop, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit (0);
		if (ft_strncmp(line, stop, ft_strlen(stop) + 1))
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			delete_mem(line);
		}
		else
			exit(0);
	}
}

static void	here_doc_exec(char *stop, int fd)
{
	int		pid;
	int		status;

	status = 0;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		fork_err();
	if (pid == 0)
	{
		rl_catch_signals = 1;
		signal(SIGINT, foo);
		readline_heredoc(stop, fd);
	}
	waitpid(pid, &status, 0);
}

int	here_doc_handle(t_mini *mshell, t_cmd *curr, char *stop_word)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		pipe_err();
		return (1);
	}
	here_doc_exec(stop_word, fd[1]);
	handle_sigs(SIGINT, mshell);
	close(fd[1]);
	curr->redir_in = fd[0];
	return (0);
}

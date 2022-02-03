/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:25:04 by tgrounds          #+#    #+#             */
/*   Updated: 2022/02/09 15:25:46 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_loop(t_mini *mshell)
{
	check_pipe_or_cmd(mshell);
	if (mshell->cmds)
		free_strarr(mshell->cmds);
	delete_list_cmd(mshell->head_cmd);
	delete_list_word(mshell->head_word);
}

int	main(int ac, char **av, char **env)
{
	t_mini	*main;
	char	*line;
	int		flag;

	(void)ac;
	(void)av;
	main = init_struct_mini(env);
	inc_shlvl(main->head_env);
	inc_shlvl(main->hidden);
	flag = -1;
	while (1)
	{
		handle_sigs(ac, main);
		line = readline(PROMPT);
		if (!line)
		{
			printf("\033[1A☣ minishell ▸ exit\n");
			exit(g_last_exit_code);
		}
		flag = parsing(line, main);
		add_history(line);
		if (flag == 0)
			free_loop(main);
		delete_mem(line);
	}
}

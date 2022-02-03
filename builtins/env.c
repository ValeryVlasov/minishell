/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:18:47 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:18:50 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env)
{
	g_last_exit_code = 0;
	if (!get_key(env, "PATH"))
	{
		print_err("env", NULL, "command not found\n");
		return ;
	}
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->str, STDOUT);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->str, STDOUT);
	else
		g_last_exit_code = 1;
}

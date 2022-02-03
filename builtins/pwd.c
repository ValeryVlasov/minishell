/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:12:44 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:12:51 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	g_last_exit_code = 0;
	if (getcwd(cwd, PATH_MAX) != 0)
		ft_putendl_fd(cwd, 1);
	else
	{
		print_error("pwd", NULL);
		g_last_exit_code = 1;
	}
}

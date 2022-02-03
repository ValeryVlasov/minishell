/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:48:05 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/09 15:48:56 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	invalid_lvl(const char *str)
{
	int		i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
	}
	return (0);
}

static int	get_lvl(const char *env_str)
{
	int		i;
	int		sign;
	int		num;

	i = 0;
	sign = 1;
	num = 0;
	if (invalid_lvl(env_str))
		return (0);
	if (env_str[i] == '-')
		sign = -1;
	if (env_str[i] == '-' || env_str[i] == '+')
		i++;
	while (env_str[i] >= '0' && env_str[i] <= '9')
		num = num * 10 + (env_str[i++] - '0');
	return (num * sign);
}

void	inc_shlvl(t_env *env)
{
	char	*shell_level_val;
	int		shlvl;
	char	*shlvl_str;

	shell_level_val = get_env_val("SHLVL", env);
	if (ft_strcmp(shell_level_val, "") == 0)
		return ;
	shlvl = get_lvl(shell_level_val) + 1;
	delete_mem(shell_level_val);
	while (env && env->str)
	{
		if (ft_strncmp("SHLVL=", env->str, 6) == 0)
		{
			delete_mem(env->str);
			shlvl_str = ft_itoa(shlvl);
			env->str = ft_strjoin("SHLVL=", shlvl_str);
			delete_mem(shlvl_str);
			return ;
		}
		env = env->next;
	}
}

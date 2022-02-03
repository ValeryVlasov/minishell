/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:16:25 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/12 14:17:07 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*add_last(t_env *hidden, char *arg)
{
	t_env	*find;

	find = hidden;
	while (find)
	{
		if (!find->next)
		{
			find->next = new_node_env(ft_strdup(arg));
			return (hidden);
		}
		find = find->next;
	}
	return (NULL);
}

char	*take_name(char *full_name)
{
	char	*addr;

	addr = full_name;
	while (*full_name)
	{
		if (*full_name == '/')
			addr = full_name;
		full_name++;
	}
	return (addr + 1);
}

int	ft_access(char *path)
{
	if (access(path, F_OK) == -1
		|| access(path, R_OK) == -1
		|| access(path, W_OK) == -1)
	{
		write(2, "Minishell: ", ft_strlen("Minishell: "));
		perror(take_name(path));
	}
	else
		return (1);
	return (0);
}

int	env_size(const t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

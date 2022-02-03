/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:14:11 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:15:03 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_to_str(t_env *env)
{
	char	**env_str;
	int		i;

	env_str = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	if (!env_str)
		return (NULL);
	env_str[env_size(env)] = NULL;
	i = 0;
	while (env)
	{
		env_str[i++] = ft_strdup(env->str);
		env = env->next;
	}
	return (env_str);
}

int	size_matrix(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	sort_env(char **env, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < size - 1)
	{
		j = size - 1;
		while (j > i)
		{
			if (ft_strcmp(env[j - 1], env[j]) > 0)
			{
				temp = env[j - 1];
				env[j - 1] = env[j];
				env[j] = temp;
			}
			j--;
		}
	}
}

char	*my_get_value(char *str)
{
	char	*temp;

	temp = ft_strchr(str, '=');
	if (!temp)
		return (NULL);
	temp++;
	if (!temp)
		return (NULL);
	return (ft_strdup(temp));
}

void	print_sort_env(t_env *env)
{
	char	**sorted_env;
	char	*temp;
	int		i;

	sorted_env = env_to_str(env);
	sort_env(sorted_env, size_matrix(sorted_env));
	i = -1;
	while (sorted_env[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		temp = get_env_name(sorted_env[i]);
		ft_putstr_fd(temp, 1);
		delete_mem(temp);
		temp = my_get_value(sorted_env[i]);
		if (temp)
		{
			ft_putstr_fd("=\"", 1);
			if (temp[0])
				ft_putstr_fd(temp, 1);
			delete_mem(temp);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	free_strarr(sorted_env);
}

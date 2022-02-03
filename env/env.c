/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:42:41 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/09 15:42:42 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_env(t_env *envp, char *to_find)
{
	while (envp && ft_strncmp(envp->str, to_find, ft_strlen(to_find)))
		envp = envp->next;
	return (envp->str);
}

char	**copy_env(t_env *env)
{
	char	**env_in_arr;
	int		i;

	env_in_arr = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	if (!env_in_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		env_in_arr[i++] = ft_strdup(env->str);
		env = env->next;
	}
	env_in_arr[i] = NULL;
	return (env_in_arr);
}

char	*get_env_name(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	if (!src || !src[0])
		return (NULL);
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (src[++i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

static char	*get_value(char *str)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	value = (char *)malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!value)
		return (NULL);
	j = 0;
	while (str[++i])
		value[j++] = str[i];
	value[j] = '\0';
	return (value);
}

char	*get_env_val(char *name, t_env *env)
{
	char	*env_value;
	char	*env_name;

	env_value = ft_strdup("");
	while (env && env->str)
	{
		env_name = get_env_name(env->str);
		if (ft_strcmp(name, env_name) == 0)
		{
			delete_mem(env_value);
			delete_mem(env_name);
			env_value = get_value(env->str);
			return (env_value);
		}
		delete_mem(env_name);
		env = env->next;
	}
	return (env_value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noda_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:52:31 by aizetta           #+#    #+#             */
/*   Updated: 2022/01/12 14:49:02 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_env(t_env *list)
{
	t_env	*tmp;
	t_env	*next;

	tmp = list;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		delete_mem(tmp->str);
		delete_mem(tmp);
		tmp = next;
	}
}

t_env	*new_node_env(char *data)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->str = data;
	env->next = NULL;
	return (env);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*save;
	int		i;

	i = 0;
	if (envp && envp[0])
		env = new_node_env(ft_strdup(envp[0]));
	else
		return (NULL);
	save = env;
	while (envp[++i])
	{
		env->next = new_node_env(ft_strdup(envp[i]));
		env = env->next;
	}
	return (save);
}

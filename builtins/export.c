/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:19:43 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:20:52 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_name(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	while (*key && (*key) != '=')
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

t_env	*find_key(t_env *src, char *to_find)
{
	char	*key;

	while (src)
	{
		key = get_env_name(to_find);
		if (!ft_strncmp(src->str, key, ft_strlen(key))
			&& (src->str[ft_strlen(key)] == '='
				|| !src->str[ft_strlen(key)]))
		{
			delete_mem(key);
			return (src);
		}
		src = src->next;
		delete_mem(key);
	}
	return (NULL);
}

static t_env	*add_env_hidden(t_env *hidden, char *arg)
{
	t_env	*find;
	t_env	*temp;

	find = find_key(hidden, arg);
	if (!find)
	{
		if (!hidden)
			return (new_node_env(ft_strdup(arg)));
		if (add_last(hidden, arg))
			return (hidden);
	}
	if (ft_strchr(arg, '='))
	{
		temp = hidden;
		while (temp != find)
			temp = temp->next;
		delete_mem(temp->str);
		temp->str = ft_strdup(arg);
	}
	return (hidden);
}

static t_env	*add_env_main(t_env *env, char *arg)
{
	t_env	*find;
	t_env	*temp;

	find = find_key(env, arg);
	if (!find)
	{
		if (!env)
			return (new_node_env(ft_strdup(arg)));
		find = env;
		while (find)
		{
			if (!find->next)
			{
				find->next = new_node_env(ft_strdup(arg));
				return (env);
			}
			find = find->next;
		}
	}
	temp = env;
	while (temp != find)
		temp = temp->next;
	delete_mem(temp->str);
	temp->str = ft_strdup(arg);
	return (env);
}

void	ft_export(t_mini *mshell, char **args)
{
	int		i;

	g_last_exit_code = 0;
	if (!args[1])
	{
		print_sort_env(mshell->hidden);
		return ;
	}
	i = 0;
	while (args[++i])
	{
		if (args[i][0] && is_valid_name(args[i]) > 0)
		{
			mshell->hidden = add_env_hidden(mshell->hidden, args[i]);
			if (ft_strchr(args[i], '='))
				mshell->head_env = add_env_main(mshell->head_env, args[i]);
		}
		else
		{
			print_err(args[0], args[i], "not a valid identifier\n");
			g_last_exit_code = 1;
		}
	}
}

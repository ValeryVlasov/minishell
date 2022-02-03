/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:13:12 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:14:02 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	invalid(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (1);
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (1);
		arg++;
	}
	return (0);
}

static void	del_key(t_mini *ms, char *key)
{
	t_env	*del;
	t_env	*save;

	del = NULL;
	save = ms->head_env;
	while (save)
	{
		if (!ft_strncmp(save->str, key, ft_strlen(key))
			&& (save->str[ft_strlen(key)] == '='
				|| !save->str[ft_strlen(key)]))
		{
			if (!del)
				ms->head_env = ms->head_env->next;
			else
				del->next = save->next;
			save->next = NULL;
			delete_mem(save->str);
			delete_mem(save);
			return ;
		}
		del = save;
		save = save->next;
	}
}

static void	del_key_h(t_mini *ms, char *key)
{
	t_env	*del;
	t_env	*save;

	del = NULL;
	save = ms->hidden;
	while (save)
	{
		if (!ft_strncmp(save->str, key, ft_strlen(key))
			&& (save->str[ft_strlen(key)] == '='
				|| !save->str[ft_strlen(key)]))
		{
			if (!del)
				ms->head_env = ms->head_env->next;
			else
				del->next = save->next;
			save->next = NULL;
			delete_mem(save->str);
			delete_mem(save);
			return ;
		}
		del = save;
		save = save->next;
	}
}

void	ft_unset(t_mini *mshell, t_cmd *cmd)
{
	int	i;

	g_last_exit_code = 0;
	i = 0;
	while (cmd->cmds[++i])
	{
		if (invalid(cmd->cmds[i]))
			print_err("unset", cmd->cmds[i], "not a valid identifier\n");
		else
		{
			if (!ft_strcmp(cmd->cmds[i], "PATH"))
				mshell->is_path = 0;
			del_key(mshell, cmd->cmds[i]);
			del_key_h(mshell, cmd->cmds[i]);
		}
	}
}

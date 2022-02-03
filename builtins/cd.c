/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:16:23 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/11 19:17:37 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_key(t_env *env, char *to_find)
{
	while (env)
	{
		if (!ft_strncmp(env->str, to_find, ft_strlen(to_find))
			&& (!env->str[ft_strlen(to_find)]
				|| env->str[ft_strlen(to_find)] == '='))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	set_value(t_env *env, char *to_set)
{
	char	*temp;

	temp = get_env_name(to_set);
	while (env)
	{
		if (!ft_strncmp(env->str, temp, ft_strlen(temp))
			&& (env->str[ft_strlen(temp)] == '='
				|| !env->str[ft_strlen(temp)]))
		{
			delete_mem(env->str);
			delete_mem(temp);
			env->str = to_set;
			return ;
		}
		env = env->next;
	}
	delete_mem(temp);
}

static void	update_pwd(t_env *env)
{
	char	*temp;
	char	*save;
	char	buf[PATH_MAX];

	save = get_key(env, "PWD")->str;
	save = ft_strdup(ft_strchr(save, '=') + 1);
	temp = ft_strjoin("OLDPWD=", save);
	delete_mem(save);
	set_value(env, temp);
	getcwd(buf, PATH_MAX);
	temp = ft_strjoin("PWD=", buf);
	set_value(env, temp);
}

static int	change_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		print_err("cd", path, strerror(errno));
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	else
	{
		closedir(dir);
		if (chdir(path) == -1)
		{
			print_err("cd", path, strerror(errno));
			ft_putstr_fd("\n", 2);
			return (-1);
		}
	}
	return (0);
}

void	ft_cd(t_mini *mshell, char **cmd, int argc)
{
	g_last_exit_code = 0;
	if (!cmd)
		return ;
	if (argc <= 1)
	{
		print_err(cmd[0], NULL, "Too few arguments\n");
		g_last_exit_code = 1;
	}
	else if (argc > 2)
	{
		print_err(cmd[0], NULL, "Too many arguments\n");
		g_last_exit_code = 1;
	}
	else
	{
		if (change_dir(cmd[1]) == -1)
			return ;
		update_pwd(mshell->head_env);
		update_pwd(mshell->hidden);
		return ;
	}
}

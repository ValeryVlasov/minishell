/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:43:31 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/14 17:52:53 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_cmd(t_env *envp, char *command)
{
	char	**paths;
	char	*cur_path;
	char	*respath;
	int		i;

	if (!access(command, X_OK))
		return (ft_strdup(command));
	if (!command || !command[0] || !envp || !get_key(envp, "PATH"))
		return (NULL);
	paths = ft_split(ft_strchr(get_key(envp, "PATH")->str, '=') + 1, ':');
	i = -1;
	while (paths && paths[++i])
	{
		cur_path = ft_strjoin(paths[i], "/");
		respath = ft_strjoin(cur_path, command);
		delete_mem(cur_path);
		if (!access(respath, X_OK))
		{
			free_strarr(paths);
			return (respath);
		}
		delete_mem(respath);
	}
	free_strarr(paths);
	return (NULL);
}

static int	open_file(t_cmd *cmd, char *name, int is_out, int mode)
{
	int		fd;

	fd = 0;
	if (is_out > 0 || ft_access(cmd->path_with_name))
	{
		if (mode && is_out == 1)
			fd = open(cmd->path_with_name, O_CREAT | O_RDWR | O_TRUNC, mode);
		else if (mode && is_out == 2)
			fd = open(cmd->path_with_name, O_CREAT | O_RDWR | O_APPEND, mode);
		else if (!mode)
			fd = open(cmd->path_with_name, O_RDONLY);
		if (fd == -1)
		{
			print_error(name, NULL);
			return (-1);
		}
		return (fd);
	}
	g_last_exit_code = 1;
	return (-1);
}

int	change_fd(t_mini *mshell, t_cmd *cmd, int i, int is_out)
{
	char	*path;

	path = find_env(mshell->head_env, "PWD=") + 4;
	path = ft_strjoin(path, "/");
	cmd->path_with_name = ft_strjoin(path, cmd->cmds[i]);
	delete_mem(path);
	if (!is_out)
	{
		if (cmd->redir_in != -2 && cmd->redir_in != -1)
			close(cmd->redir_in);
		cmd->redir_in = open_file(cmd, cmd->cmds[i], is_out, 0);
	}
	else if (is_out)
	{
		if (cmd->redir_out != -2 && cmd->redir_out != -1)
			close(cmd->redir_out);
		cmd->redir_out = open_file(cmd, cmd->cmds[i], is_out, 0644);
	}
	if (cmd->path_with_name)
		delete_mem(cmd->path_with_name);
	return (cmd->redir_out == -1 || cmd->redir_in == -1);
}

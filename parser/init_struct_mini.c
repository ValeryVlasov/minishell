/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stuct_mini.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:52:21 by aizetta           #+#    #+#             */
/*   Updated: 2022/01/02 14:52:24 by aizetta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mini	*init_struct_mini(char **env)
{
	t_mini	*new;

	new = (t_mini *)malloc(sizeof(t_mini));
	if (!new)
		return (NULL);
	new->head_env = init_env(env);
	new->hidden = init_env(env);
	new->head_word = NULL;
	new->head_cmd = NULL;
	new->cmds = NULL;
	new->cmd_size = 0;
	new->list_size = 0;
	new->is_path = 1;
	new->sigint = NULL;
	new->sigquit = NULL;
	return (new);
}

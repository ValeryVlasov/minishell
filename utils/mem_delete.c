/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:47:41 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/09 15:47:51 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*delete_mem(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	*free_strarr(char **arr)
{
	int		i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
		{
			if (arr[i])
				delete_mem(arr[i]);
		}
		delete_mem(arr);
	}
	return (NULL);
}

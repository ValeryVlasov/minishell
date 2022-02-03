/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:09:33 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:09:35 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*list;

	if (!*lst)
		*lst = new;
	else
	{
		list = new;
		list->next = *lst;
		*lst = list;
	}
}

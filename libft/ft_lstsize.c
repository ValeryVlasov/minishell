/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:13 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:10:14 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		num;
	t_list	*list;

	num = 0;
	list = lst;
	while (list)
	{
		num++;
		list = list->next;
	}
	return (num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:02 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:10:03 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*new;

	if (!f || !lst)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	first = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew((*f)(lst->content));
		if (!new->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (first);
}

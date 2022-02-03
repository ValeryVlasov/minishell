/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:11:32 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:11:34 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	sym;

	ptr = (char *) s;
	sym = (char) c;
	while (*ptr)
	{
		if (*ptr == sym)
			return (ptr);
		ptr++;
	}
	if (*ptr == sym)
		return (ptr);
	return (NULL);
}

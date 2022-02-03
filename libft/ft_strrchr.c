/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:12:17 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:12:18 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	*last;
	char	sym;

	sym = (char) c;
	ptr = (char *) s;
	last = NULL;
	while (*ptr)
	{
		if (*ptr == sym)
			last = ptr;
		ptr++;
	}
	if (*ptr == sym)
		return (ptr);
	return (last);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:29 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:10:29 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	sym;

	ptr = (unsigned char *) arr;
	sym = (unsigned char) c;
	while (n--)
	{
		if (*ptr == sym)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

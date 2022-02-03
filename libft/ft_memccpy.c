/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:19 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:10:20 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t count)
{
	unsigned char		*ptr_d;
	const unsigned char	*ptr_s;
	unsigned char		sym;

	ptr_d = (unsigned char *)dest;
	ptr_s = (const unsigned char *)src;
	sym = (unsigned char)c;
	while (count--)
	{
		*ptr_d++ = *ptr_s++;
		if (*(ptr_d - 1) == sym)
			return (&*ptr_d);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:42 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:10:43 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	unsigned char	*ptr_d;
	unsigned char	*ptr_s;

	ptr_d = (unsigned char *) dest;
	ptr_s = (unsigned char *) src;
	if (dest == src)
		return (dest);
	while (count--)
		*ptr_d++ = *ptr_s++;
	return (dest);
}

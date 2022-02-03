/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:33 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:10:34 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (const unsigned char *) buf1;
	ptr2 = (const unsigned char *) buf2;
	while (count--)
	{
		if (*ptr1 != *ptr2)
			return ((int)*ptr1 - (int)*ptr2);
		ptr1++;
		ptr2++;
	}
	return (0);
}

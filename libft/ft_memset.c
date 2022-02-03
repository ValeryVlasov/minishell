/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:56 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:10:58 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*temp;
	unsigned char	sym;

	temp = (unsigned char *) ptr;
	sym = (unsigned char) value;
	while (num--)
		*temp++ = value;
	return (ptr);
}

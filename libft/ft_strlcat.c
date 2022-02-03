/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:11:48 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:11:49 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_min(size_t f, size_t s)
{
	if (f < s)
		return (f);
	return (s);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	res;
	size_t	dsize;

	dsize = ft_strlen(dst);
	res = ft_min(dstsize, dsize) + ft_strlen(src);
	if (dsize < dstsize)
	{
		dst += dsize;
		dstsize -= dsize;
		while (*src && dstsize-- > 1)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (res);
}

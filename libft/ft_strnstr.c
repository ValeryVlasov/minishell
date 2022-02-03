/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:12:08 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:12:09 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_length;
	size_t	i;
	size_t	j;
	char	*hay;

	hay = (char *) haystack;
	needle_length = ft_strlen(needle);
	if (!needle_length)
		return (hay);
	if ((size_t)ft_strlen(haystack) < needle_length
		|| len < needle_length)
		return (NULL);
	i = 0;
	while (hay[i] && i <= len - needle_length)
	{
		j = 0;
		while (needle[j] && needle[j] == hay[i + j])
			j++;
		if (j == needle_length)
			return (&hay[i]);
		i++;
	}
	return (NULL);
}

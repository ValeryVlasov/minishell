/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 13:28:26 by tgrounds          #+#    #+#             */
/*   Updated: 2021/10/03 13:29:11 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (*str1 && *str2)
		if (*str1++ != *str2++)
			return ((unsigned char)*--str1 - (unsigned char)*--str2);
	if (!*str1 && !*str2)
		return (0);
	return (-1);
}

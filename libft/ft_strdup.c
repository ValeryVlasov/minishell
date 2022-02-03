/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:11:36 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:11:37 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*result;
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)str;
	result = (char *) malloc(sizeof(char) * (ft_strlen(ptr) + 1));
	if (!result)
		return (NULL);
	while (ptr[i])
	{
		result[i] = ptr[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

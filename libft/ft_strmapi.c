/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:12:00 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:12:01 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = ft_strdup(s);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = (*f)(i, (char)s[i]);
		i++;
	}
	return (result);
}

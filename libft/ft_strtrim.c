/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:12:21 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:12:22 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_sym(const char s, const char *set_str)
{
	int		i;

	i = 0;
	while (set_str[i])
		if (set_str[i++] == s)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	begin;
	size_t	end;

	if (!s1)
		return (NULL);
	begin = 0;
	while (find_sym(s1[begin], set) && s1[begin])
		begin++;
	end = ft_strlen(s1);
	while (end > begin && find_sym(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(s1[0]) * (end - begin + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < end - begin)
	{
		str[i] = s1[begin + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

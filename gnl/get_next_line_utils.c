/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:48:35 by aizetta           #+#    #+#             */
/*   Updated: 2021/11/13 21:02:26 by aizetta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_memcpy_gnl(char *dest, char *src, size_t n)
{
	size_t			i;
	unsigned char	*pr1;
	unsigned char	*pr2;

	i = 0;
	pr1 = (unsigned char *) dest;
	pr2 = (unsigned char *) src;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		*(pr1 + i) = *(pr2 + i);
		i++;
	}
	return (dest);
}

char	*ft_strdup_gnl(char *src)
{
	char	*new_src;
	size_t	i;

	i = ft_strlen_gnl(src);
	new_src = (void *)malloc((i + 1) * sizeof (char));
	if (!new_src)
		return (0);
	ft_memcpy_gnl(new_src, src, i);
	new_src[i] = '\0';
	return (new_src);
}

char	*ft_substr_gnl(char *big_str, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	if (!big_str || len <= 0 || start >= ft_strlen_gnl(big_str))
		return (ft_strdup_gnl(""));
	if (ft_strlen_gnl(big_str) < len)
		len = ft_strlen_gnl(big_str);
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = start;
	while (big_str[i] != '\0' && len > (i - start))
	{
		new_str[i - start] = big_str[i];
		i++;
	}
	new_str[i - start] = '\0';
	return (new_str);
}

char	*my_strjoin_gnl(char *s1, char *s2)
{
	size_t	str_len1;
	size_t	str_len2;
	size_t	sum;
	char	*fin;

	if (!s1 && !s2)
		return (0);
	str_len1 = ft_strlen_gnl((char *)s1);
	str_len2 = ft_strlen_gnl((char *)s2);
	sum = str_len1 + str_len2;
	fin = (char *) malloc(sizeof (char) * (sum + 1));
	if (!fin)
		return (0);
	ft_memcpy_gnl(fin, s1, str_len1);
	ft_memcpy_gnl(fin + str_len1, s2, str_len2);
	fin[str_len1 + str_len2] = '\0';
	free((char *)s1);
	return (fin);
}

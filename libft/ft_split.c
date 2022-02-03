/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:11:22 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:11:23 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cnt_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (i == 0 && s[i] && s[i] != c)
			count++;
		if (i > 0 && s[i] && s[i - 1] == c)
			count++;
		if (s[i])
			i++;
	}
	if (count == 0 && s[i - 1] == c)
		return (0);
	return (count);
}

int	check_mem(char **strs, size_t i)
{
	if (!strs[i])
	{
		while (--i >= 0)
			free(strs[i]);
		free(strs);
		return (0);
	}
	return (1);
}

char	**mal(char **strs, char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] != c)
			count++;
		else if (j > 0 && s[j - 1] != c)
		{
			strs[i++] = malloc(sizeof(char) * (count + 1));
			if (!strs[i - 1])
				return (0);
		}
		if (s[++j] == '\0' && s[j - 1] != c)
		{
			strs[i] = malloc(sizeof(char) * (count + 1));
			if (!strs[i])
				return (0);
		}
	}
	return (strs);
}

char	**copy(char **strs, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[k])
	{
		if (s[k] != c)
			strs[i][j++] = s[k];
		else if (k > 0 && s[k - 1] != c)
		{
			strs[i][j] = '\0';
			j = 0;
			i++;
		}
		if (s[k + 1] == '\0' && s[k] != c)
			strs[i][j] = '\0';
		k++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**str;

	if (!s)
		return (NULL);
	i = cnt_words(s, c);
	str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = NULL;
	str = mal(str, s, c);
	if (!str)
	{
		while (i >= 0)
		{
			if (str[i])
				free(str[i]);
			i--;
		}
		free(str);
		return (NULL);
	}
	str = copy(str, s, c);
	return (str);
}

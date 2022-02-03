/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:09:21 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:09:22 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*empty(void)
{
	char	*emp_str;

	emp_str = (char *)malloc(2);
	if (!emp_str)
		return (NULL);
	emp_str[0] = '0';
	emp_str[1] = '\0';
	return (emp_str);
}

char	*to_str(char *digits, int size)
{
	size_t	i;
	int		j;
	char	*res;

	if (digits[10] == '-')
		res = (char *)malloc(size + 2);
	else
		res = (char *)malloc(size + 1);
	if (!res)
		return (NULL);
	j = size - 1;
	i = 0;
	if (digits[10] == '-')
		res[i++] = '-';
	while (j >= 0)
		res[i++] = digits[j--];
	res[i] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	long	nbr;
	size_t	i;
	char	str[11];

	nbr = n;
	i = 0;
	str[10] = 0;
	if (nbr == 0)
		return (empty());
	if (nbr < 0)
	{
		nbr = -nbr;
		str[10] = '-';
	}
	while (nbr > 0)
	{
		str[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (to_str(str, i));
}

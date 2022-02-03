/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:11:14 by tgrounds          #+#    #+#             */
/*   Updated: 2021/11/10 13:11:16 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_abs(int n)
{
	unsigned long	res;

	if (n < 0)
		res = n * (-1);
	else
		res = n;
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (fd < 0)
		return ;
	if (n < 0)
		ft_putchar_fd('-', fd);
	num = (unsigned)ft_abs(n);
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
		ft_putchar_fd(num + '0', fd);
}

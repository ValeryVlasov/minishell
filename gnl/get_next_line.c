/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:48:21 by aizetta           #+#    #+#             */
/*   Updated: 2021/11/13 20:48:26 by aizetta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	exit_flag(char *fin)
{
	size_t	i;

	i = 0;
	if (!fin)
		return (1);
	while (fin[i])
	{
		if (fin[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*newline(char *save)
{
	size_t	i;
	char	*fin;

	i = 0;
	if (!save)
		return (0);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	fin = ft_substr_gnl(save, 0, i);
	return (fin);
}

char	*new_save(char *save)
{
	size_t	i;
	char	*fin;

	i = 0;
	if (!save)
		return (0);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (0);
	}
	fin = ft_substr_gnl(save, i + 1, ft_strlen_gnl(save) - i);
	free(save);
	return (fin);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*save;
	ssize_t		flag;

	if (BUFFER_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	flag = 1;
	while (exit_flag(save) && flag != 0)
	{
		flag = read(fd, buf, BUFFER_SIZE);
		buf[flag] = '\0';
		if (flag == -1)
			return (-1);
		save = my_strjoin_gnl(save, buf);
	}
	*line = newline(save);
	save = new_save(save);
	if (flag == 0)
		return (0);
	return (1);
}

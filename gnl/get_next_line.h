/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrounds <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:52:45 by tgrounds          #+#    #+#             */
/*   Updated: 2022/01/12 14:52:46 by tgrounds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		get_next_line(int fd, char **line);
size_t	ft_strlen_gnl(char *s);
char	*ft_memcpy_gnl(char *dest, char *src, size_t n);
char	*ft_strdup_gnl(char *src);
char	*ft_substr_gnl(char *big_str, unsigned int start, size_t len);
char	*my_strjoin_gnl(char *s1, char *s2);
int		exit_flag(char *fin);
char	*newline(char *save);
char	*new_save(char *save);

#endif

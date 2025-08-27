/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:52 by fekiz             #+#    #+#             */
/*   Updated: 2025/08/27 18:52:08 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "unistd.h"
# include "stdlib.h"
# include "fcntl.h"
# include "stdbool.h"
# include "stdio.h"

char	*get_next_line(int fd);
char	*ft_get_st(int fd, char *st);
char	*ft_strjoin(char *s1, char *s2);
int		search_nl(char *st);
size_t	ft_strlen(const char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:32:39 by fekiz             #+#    #+#             */
/*   Updated: 2025/08/30 17:57:51 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "unistd.h"
# include "stdlib.h"
# include "stdbool.h"

char	*get_next_line(int fd);
char	*ft_get_st(int fd, char *st);
char	*ft_strjoin(char *s1, char *s2);
int		search_nl(char *st);
size_t	ft_strlen(const char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 12:22:27 by fekiz             #+#    #+#             */
/*   Updated: 2023/10/28 20:48:10 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcpy(char *s1, char *s2);
int		ft_check_new_line(char *str);

char	*get_next_line(int fd);
char	*ft_get_read(int fd, char *statik);
char	*ft_liner(char *statik);
char	*get_new_statik(char *temp_statik, char *line);
char	*ft_new_static(char *statik, char *line);

#endif

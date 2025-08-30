/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:54 by fekiz             #+#    #+#             */
/*   Updated: 2025/08/30 17:56:17 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*continue_get_st(int len, char *temp, char *st)
{
	free(temp);
	if (len == 0 || len == -1)
	{
		if (st && st[0] == '\0')
		{
			free(st);
			return (NULL);
		}
		return (st);
	}
	free(st);
	return (NULL);
}

char	*ft_get_st(int fd, char *st)
{
	int		len;
	char	*temp;

	if (!st)
	{
		st = malloc(1);
		if (st)
			st[0] = '\0';
	}
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp || !st)
		return (NULL);
	while (true)
	{
		len = read(fd, temp, BUFFER_SIZE);
		if (len <= 0)
			return (continue_get_st(len, temp, st));
		temp[len] = '\0';
		st = ft_strjoin(st, temp);
		if (!st)
			return (free(temp), NULL);
		if (search_nl(st) > 0)
			break ;
	}
	return (free(temp), st);
}

char	*get_new_line(char *st)
{
	int		i;
	char	*line;

	if (!st || st[0] == '\0')
		return (NULL);
	i = search_nl(st);
	if (i > 0)
		line = malloc(i + 1);
	else
		line = malloc(ft_strlen(st) + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (st[i] && st[i] != '\n')
	{
		line[i] = st[i];
		i++;
	}
	if (st[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*st;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(st);
		st = NULL;
		return (NULL);
	}
	st = ft_get_st(fd, st);
	if (!st)
		return (NULL);
	new_line = get_new_line(st);
	st = set_new_st(st);
	return (new_line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:54 by fekiz             #+#    #+#             */
/*   Updated: 2025/08/29 12:46:57 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*continue_get_st(int len, char *temp, char *st)
{
	if (len == 0)
	{
		free(temp);
		if (st && st[0] == '\0')
		{
			free(st);
			st = NULL;
		}
		return (st);
	}
	return (NULL);
}

char	*ft_get_st(int fd, char *st, int index)
{
	int		len;
	char	*temp;

	len = -1;
	temp = ft_calloc(index + 1, 1);
	if (!temp)
		return (NULL);
	while (true)
	{
		len = read(fd, temp, index);
		if (len <= 0)
		{
			if (len == 0)
				return (continue_get_st(len, temp, st));
			return (free(temp), free(st), NULL);
		}
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

	i = search_nl(st);
	if (i > 0)
		line = ft_calloc(i + 2, 1);
	else if (i == -1)
		line = ft_calloc(ft_strlen(st) + 1, 1);
	else if (i == 0)
		return (NULL);
	if (!line)
		return (NULL);
	i = 0;
	while (st[i])
	{
		if (st[i] == '\n')
			break ;
		line[i] = st[i];
		i++;
	}
	if (search_nl(st) != -1)
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*set_new_st(char *st)
{
	int		i;
	int		j;
	char	*new_st;

	i = 0;
	j = 0;
	if (!st)
		return (NULL);
	while (st[i] && st[i] != '\n')
		i++;
	if (!st[i])
		return (free(st), NULL);
	i++;
	new_st = ft_calloc(ft_strlen(st + i) + 1, 1);
	if (!new_st)
		return (free(st), NULL);
	while (st[i])
		new_st[j++] = st[i++];
	new_st[j] = '\0';
	free(st);
	return (new_st);
}

char	*get_next_line(int fd)
{
	static char	*st[10240];
	char		*new_line;
	long long	temp;

	new_line = NULL;
	temp = BUFFER_SIZE;
	if (fd < 0 || temp <= 0 || (read(fd, NULL, 0) < 0))
	{
		if (st[fd])
			free(st[fd]);
		return (NULL);
	}
	st[fd] = ft_get_st(fd, st[fd], temp);
	if (!st[fd] || st[fd][0] == '\0')
		return (NULL);
	new_line = get_new_line(st[fd]);
	st[fd] = set_new_st(st[fd]);
	return (new_line);
}

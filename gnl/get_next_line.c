/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:54 by fekiz             #+#    #+#             */
/*   Updated: 2025/08/27 19:38:39 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_new_line(char *st)
{
	int		i;
	char	*line;

	i = search_nl(st);
	if (i > 0)
		line = malloc(i + 2);
	else if (i == -1)
		line = malloc(ft_strlen(st) + 1);
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
	char	*temp;

	temp = malloc(ft_strlen(st) + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (st[i] && st[i] != '\n')
		i++;
	j = 0;
	while (st[++i])
		temp[j++] = st[i];
	free(st);
	temp[j] = '\0';
	st = malloc(ft_strlen(temp) + 1);
	if (!st)
		return (free(temp), NULL);
	i = -1;
	while (temp[++i])
		st[i] = temp[i];
	st[i] = '\0';
	return (st);
}

char	*get_next_line(int fd)
{
	static char	*st;
	char		*new_line;
	long long	temp;

	new_line = NULL;
	temp = BUFFER_SIZE;
	if (fd < 0 || temp <= 0 || temp >= 2147483647 || (read(fd, NULL, 0) < 0))
	{
		if (st)
			free(st);
		return (NULL);
	}
	st = ft_get_st(fd, st, temp);
	if (!st || st[0] == '\0')
		return (NULL);
	new_line = get_new_line(st);
	st = set_new_st(st);
	return (new_line);
}

int main()
{
	int fd = open("test", O_RDONLY, 777);
	// char *test = get_next_line(fd);
	// (void)test;
	for (int i = 0; i <= 5; i++)
		printf("%s", get_next_line(fd));
}

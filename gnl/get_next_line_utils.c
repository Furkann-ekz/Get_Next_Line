/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:48 by fekiz             #+#    #+#             */
/*   Updated: 2025/08/27 18:57:24 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	search_nl(char *st)
{
	int	i;

	if (!st || st[0] == '\0')
		return (-1);
	i = 0;
	while (st[i])
	{
		if (st[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static void	ft_next_join(char *s1, char *s2, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (free(s1), NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	str = malloc(i + j + 1);
	if (!str)
		return (free(s1), NULL);
	ft_next_join(s1, s2, str);
	free(s1);
	return (str);
}

char	*ft_get_st(int fd, char *st)
{
	int		len;
	char	temp[BUFFER_SIZE + 1];

	len = -1;
	while (true)
	{
		len = read(fd, temp, BUFFER_SIZE);
		if (len <= 0)
		{
			if (len == 0)
				return (st);
			return (NULL);
		}
		temp[len] = '\0';
		st = ft_strjoin(st, temp);
		if (search_nl(st) > 0)
			break ;
		if (!st)
			return (NULL);
	}
	return (st);
}

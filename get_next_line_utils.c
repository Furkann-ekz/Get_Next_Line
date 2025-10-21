/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:48 by fekiz             #+#    #+#             */
/*   Updated: 2025/08/30 15:53:57 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	search_nl(char *st)
{
	int	i;

	i = 0;
	if (!st)
		return (-1);
	while (st[i])
	{
		if (st[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
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
	free(s1);
	s1 = NULL;
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
	if (!s2)
		return (free(s1), NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	str = malloc(i + j + 1);
	if (!str)
		return (free(s1), NULL);
	ft_next_join(s1, s2, str);
	return (str);
}

char	*set_new_st(char *st)
{
	int		i;
	int		j;
	char	*new_st;

	if (!st)
		return (NULL);
	i = 0;
	while (st[i] && st[i] != '\n')
		i++;
	if (st[i] == '\n')
		i++;
	if (st[i] == '\0')
	{
		free(st);
		return (NULL);
	}
	new_st = malloc(ft_strlen(st + i) + 1);
	if (!new_st)
		return (free(st), NULL);
	j = 0;
	while (st[i])
		new_st[j++] = st[i++];
	new_st[j] = '\0';
	free(st);
	return (new_st);
}

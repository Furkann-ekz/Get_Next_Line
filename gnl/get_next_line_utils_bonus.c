/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:48 by fekiz             #+#    #+#             */
/*   Updated: 2025/08/28 13:39:35 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	search_nl(char *st)
{
	int	i;

	if (!st || st[0] == '\0')
		return (0);
	i = 0;
	while (st[i])
	{
		if (i == 0 && st[i] == '\n')
			return (1);
		if (i > 0 && st[i] == '\n')
			return (i);
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
		s1 = ft_calloc(1, 1);
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
	str = ft_calloc(i + j + 1, 1);
	if (!str)
		return (free(s1), NULL);
	ft_next_join(s1, s2, str);
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*p;
	size_t			i;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < count * size)
	{
		p[i] = 0;
		i ++;
	}
	return (ptr);
}

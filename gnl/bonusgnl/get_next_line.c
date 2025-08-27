/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:02:35 by fekiz             #+#    #+#             */
/*   Updated: 2024/01/14 15:50:46 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		if (str[i++] == '\n')
			return (1);
	return (0);
}

char	*ft_read(char *str, int fd)
{
	char	*temp;
	int		index;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	index = 1;
	while (!newline(str) && index != 0)
	{
		index = read(fd, temp, BUFFER_SIZE);
		if (index == -1)
		{
			if (str)
				free(str);
			free(temp);
			return (NULL);
		}
		temp[index] = '\0';
		str = ft_strjoin(str, temp);
	}
	free(temp);
	return (str);
}

char	*str_line(char *str)
{
	int		i;
	char	*s;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			break ;
	if (str[i] == '\n')
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

char	*new_str(char *str)
{
	char	*new_str;
	int		start;
	int		len;
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			break ;
	if (str[i] == '\n')
		i++;
	start = i;
	len = (ft_strlen(str) - start);
	if (len == 0)
	{
		free(str);
		return (NULL);
	}
	new_str = ft_substr(str, start, len);
	free (str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*str2;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read(str, fd);
	if (!str || !*str)
	{
		if (str)
			free(str);
		return (NULL);
	}
	str2 = str_line(str);
	str = new_str(str);
	return (str2);
}

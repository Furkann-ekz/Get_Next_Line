/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:02:35 by fekiz             #+#    #+#             */
/*   Updated: 2023/10/30 14:50:47 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_read(int fd, char *statik)
{
	char	*liner;
	int		rd;

	liner = malloc(BUFFER_SIZE + 1);
	rd = 1;
	if (!liner)
		return (NULL);
	while (rd > 0)
	{
		rd = read(fd, liner, BUFFER_SIZE);
		if (rd < 0)
		{
			free(liner);
			free(statik);
			return (NULL);
		}
		else if (rd == 0)
		{
			free(liner);
			break;
		}
		liner[rd] = '\0';
		if (rd > 0)
			statik = ft_strjoin(statik, liner);
	}
	free(liner);
	return (statik);
}

char	*ft_liner(char *statik)
{
	char	*line;
	int		i;
	int		new_line;

	if (*statik == 0)
	{
		free(statik);
		return (NULL);
	}
	new_line = ft_check_new_line(statik);
	i = 0;
	while (statik[i] && statik[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + new_line + 1));
	if (!line)
		return (NULL);
	line = ft_strcpy(line, statik);
	return (line);
}

char	*ft_new_static(char *statik, char *line)
{
	char	*temp_statik;

	temp_statik = NULL;
	if ((!*statik || !*line) || (!statik || !line))
	{
		free(statik);
		return (NULL);
	}
	temp_statik = ft_strjoin(temp_statik, statik);
	free(statik);
	statik = get_new_statik(temp_statik, line);
	free(temp_statik);
	return (statik);
}

char	*get_next_line(int fd)
{
	static char	*statik;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (statik)
			free(statik);
		return (NULL);
	}
	if (!statik)
	{
		statik = ft_get_read(fd, statik);
		if (!statik || !*statik)
		{
			if (statik)
				free(statik);
			return (NULL);
		}
	}
	line = ft_liner(statik);
	if (!line || !*line)
		return (NULL);
	statik = ft_new_static(statik, line);
	return (line);
}

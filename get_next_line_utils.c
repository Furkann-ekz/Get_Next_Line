/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:00:56 by fekiz             #+#    #+#             */
/*   Updated: 2023/10/30 14:22:19 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check_new_line(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i] != 0)
		s3[i] = s1[i];
	j = -1;
	while (s2[++j] != 0)
	{
		s3[i + j] = s2[j];
	}
	s3[i + j] = '\0';
	free(s1);
	return (s3);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2)
		return (NULL);
	while (s2[i] && s2[i] != '\n')
	{
		s1[i] = s2[i];
		i++;
	}
	if (s2[i] == '\n')
		s1[i++] = '\n';
	s1[i] = '\0';
	return (s1);
}

char	*get_new_statik(char *temp_statik, char *line)
{
	int		i;
	int		j;
	char	*new_statik;

	if (*temp_statik == 0)
	{
		free(temp_statik);
		return (NULL);
	}
	if (!temp_statik || !line)
		return (NULL);
	i = ft_strlen(line);
	j = ((ft_strlen(temp_statik) - ft_strlen(line)) + 1);
	new_statik = malloc(sizeof(char) * j);
	if (!new_statik)
		return (NULL);
	j = 0;
	while (temp_statik[i] != '\0')
	{
		new_statik[j] = temp_statik[i];
		j++;
		i++;
	}
	new_statik[j] = '\0';
	return (new_statik);
}

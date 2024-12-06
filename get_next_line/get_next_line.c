/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:01:20 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/01 16:45:25 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*result;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buffer = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = ft_read_line(fd, line, buffer);
	if (!line)
		return (NULL);
	result = save_line(line);
	line = save_next_line(line);
	return (result);
}

char	*ft_read_line(int fd, char *line_saved, char *buffer)
{
	ssize_t	n;

	n = 1;
	while (!ft_strchr_get(line_saved, '\n') && n != 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(buffer);
			free(line_saved);
			return (NULL);
		}
		buffer[n] = '\0';
		line_saved = ft_strjoin_get(line_saved, buffer);
	}
	free(buffer);
	if (line_saved[0] == '\0')
	{
		free(line_saved);
		return (NULL);
	}
	return (line_saved);
}

char	*save_line(char *s)
{
	int		i;
	char	*result;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	result = (char *)malloc(i + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		result[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		result[i++] = '\n';
	result[i] = '\0';
	return (result);
}

char	*save_next_line(char *str)
{
	int		i;
	int		j;
	char	*n_line;

	i = 0;
	j = 0;
	if (!str)
	{
		free(str);
		return (NULL);
	}
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	n_line = malloc((ft_strlen_get(str) - i) + 1);
	if (!n_line)
		return (NULL);
	while (str[i] != '\0')
		n_line[j++] = str[i++];
	n_line[j] = '\0';
	free(str);
	return (n_line);
}

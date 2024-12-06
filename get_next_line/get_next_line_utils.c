/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:33:03 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/01 16:49:57 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_get(char *src)
{
	int		l;
	char	*p1;

	l = 0;
	p1 = (char *)malloc(ft_strlen_get(src) + 1);
	if (p1 == NULL)
	{
		free(p1);
		return (NULL);
	}
	if (src[l] == '\0')
		p1[l] = '\0';
	while (src[l])
	{
		p1[l] = src[l];
		l++;
	}
	p1[l] = '\0';
	return (p1);
}

char	*ft_strjoin_get(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_get(s2));
	ptr = (char *)malloc(ft_strlen_get(s1) + ft_strlen_get(s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

size_t	ft_strlen_get(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_get(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		else
			i++;
	}
	return (NULL);
}

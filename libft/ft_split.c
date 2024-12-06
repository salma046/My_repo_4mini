/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:17:33 by salaoui           #+#    #+#             */
/*   Updated: 2023/12/08 20:52:34 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count_w;
	int	i;

	i = 0;
	count_w = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count_w++;
		i++;
	}
	return (count_w);
}

static void	ft_str(char *ptr, char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
}

static int	free_memory(char **arrs_ptr, int index)
{
	while (index-- > 0)
		free(arrs_ptr[index]);
	free(arrs_ptr);
	return (0);
}

static int	allocate_words(char const *s, char c, char **arrs_ptr)
{
	int	j;
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j] && s[i + j] != c)
				j++;
			arrs_ptr[n] = malloc(j + 1);
			if (arrs_ptr[n] == NULL)
				return (free_memory(arrs_ptr, n));
			ft_str(arrs_ptr[n], c, s + i);
			i = i + j;
			n++;
		}
		else
			i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		count_w;
	char	**arrs_ptr;

	if (!s)
		return (NULL);
	count_w = count_words(s, c);
	arrs_ptr = malloc((count_w + 1) * sizeof(char *));
	if (!arrs_ptr)
		return (NULL);
	if (allocate_words(s, c, arrs_ptr) == 0)
		return (NULL);
	arrs_ptr[count_w] = 0;
	return (arrs_ptr);
}

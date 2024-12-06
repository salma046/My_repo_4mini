/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:32:16 by salaoui           #+#    #+#             */
/*   Updated: 2023/11/30 12:31:38 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char c, char const *set)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (set[j] == c)
		{
			return (1);
		}
		j++;
	}
	return (0);
}

static char	*ft_finish(int i, int end, char const *str, char *ptr)
{
	int	k;

	k = 0;
	while (i < end)
	{
		ptr[k] = str[i];
		k++;
		i++;
	}
	ptr[k] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	i = 0;
	while (i < end && ft_check(s1[i], set) == 1)
	{
		i++;
	}
	while (end > 0 && ft_check(s1[end - 1], set) == 1)
	{
		end--;
	}
	if (end < i)
		return (ft_strdup(""));
	ptr = malloc((end - i + 1) * sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (ft_finish(i, end, s1, ptr));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:12:03 by salaoui           #+#    #+#             */
/*   Updated: 2023/12/08 20:54:16 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*comp_func(const char *s, const char *need, size_t i, size_t l)
{
	const char	*temp_s1;
	const char	*temp_s2;
	int			t;

	temp_s1 = s;
	temp_s2 = need;
	if (*s == *need)
		t = i;
	while (*temp_s2 != '\0' && *temp_s1 == *temp_s2 && i < l)
	{
		temp_s1++;
		temp_s2++;
		i++;
	}
	if (*temp_s2 != '\0')
	{
		i = t;
		return (NULL);
	}
	if (*temp_s2 == '\0')
	{
		return ((char *)(s));
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*result;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && i < len)
	{
		result = comp_func(haystack, needle, i, len);
		if (result != NULL)
			return (result);
		haystack++;
		i++;
	}
	return (0);
}

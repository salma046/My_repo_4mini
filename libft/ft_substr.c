/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:01:50 by salaoui           #+#    #+#             */
/*   Updated: 2023/12/09 12:17:52 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	l;

	if (!s)
		return (NULL);
	l = 0;
	if (start >= ft_strlen(s) || len == 0)
	{
		ptr = malloc(1);
		if (ptr == NULL)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (l < len)
	{
		ptr[l++] = s[start++];
	}
	ptr[l] = '\0';
	return (ptr);
}
// int main()
// {
// 	const char *str;
// 	str ="lorem ipsu";
// 	printf("%s \n",ft_substr(str,0,10));
// }

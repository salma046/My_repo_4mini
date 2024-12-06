/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:32:09 by salaoui           #+#    #+#             */
/*   Updated: 2023/11/30 12:28:07 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		count;
	char	*str;

	str = (char *)s;
	count = ft_strlen(s);
	while (count >= 0)
	{
		if (str[count] == (char)c)
			return (&str[count]);
		count--;
	}
	return (NULL);
}

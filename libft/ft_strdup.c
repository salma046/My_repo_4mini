/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:54:55 by salaoui           #+#    #+#             */
/*   Updated: 2024/11/29 11:08:57 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		l;
	char	*p1;

	l = 0;
	p1 = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (p1 == NULL)
	{
		return (NULL);
	}
	while (src[l])
	{
		p1[l] = src[l];
		l++;
	}
	p1[l] = '\0';
	return (p1);
}

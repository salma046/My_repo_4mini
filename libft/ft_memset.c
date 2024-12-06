/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:34:47 by salaoui           #+#    #+#             */
/*   Updated: 2023/11/30 11:40:11 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*p;
	int		val;
	size_t	i;

	i = 0;
	val = c;
	p = (char *)str;
	while (i < n)
	{
		p[i] = val;
		i++;
	}
	return (str);
}

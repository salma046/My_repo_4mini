/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:12:46 by salaoui           #+#    #+#             */
/*   Updated: 2023/12/08 20:46:59 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len = 1;
	}
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*ft_putchar(char *ptr, unsigned int n, int len)
{
	while (n > 0)
	{
		ptr[len--] = 48 + (n % 10);
		n = n / 10;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*ptr;
	unsigned int	number;

	len = ft_len(n);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[len--] = '\0';
	if (n == 0)
	{
		ptr[0] = '0';
	}
	if (n < 0)
	{
		number = n * -1;
		ptr[0] = '-';
	}
	else
		number = n;
	ptr = ft_putchar(ptr, number, len);
	return (ptr);
}

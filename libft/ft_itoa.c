/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:55:42 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/27 15:01:11 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ilen(int n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		c++;
	while (n)
	{
		c++;
		n = n / 10;
	}
	return (c);
}

static char	*exception_handler(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else
		return (ft_strdup("0"));
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		len;

	len = ilen(n);
	if (n == -2147483648 || n == 0)
		return (exception_handler(n));
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return ((void *)0);
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	i = len - 1;
	while (n)
	{
		res[i] = (n % 10) + 48;
		i--;
		n = n / 10;
	}
	res[len] = '\0';
	return (res);
}

// Test Main
/*
int	main(void)
{
	printf("%s\n", ft_itoa(214748364));
} */

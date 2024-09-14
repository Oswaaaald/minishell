/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:55:42 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/13 17:34:02 by fghysbre         ###   ########.fr       */
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

static char	*exception_handler(t_prog *prog, int n)
{
	if (n == -2147483648)
		return (ft_strdup(prog, "-2147483648"));
	else
		return (ft_strdup(prog, "0"));
}

char	*ft_itoa(t_prog *prog, int n)
{
	char	*res;
	int		i;
	int		len;

	len = ilen(n);
	if (n == -2147483648 || n == 0)
		return (exception_handler(prog, n));
	res = (char *)ft_malloc(prog, (len + 1) * sizeof(char));
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

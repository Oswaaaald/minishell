/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:04:55 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/16 15:23:21 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = -1;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (++i < n)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
	}
	return (0);
}

// Test Main
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char s1[] = "test123";
	char s2[] = "test456";
	size_t n = 8;

	printf("%d (%d)\n", ft_memcmp(s1, s2, n), memcmp(s1, s2, n));
	return (0);
} */
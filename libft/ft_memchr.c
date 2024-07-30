/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:40:37 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/23 08:43:05 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*a;

	i = -1;
	a = (unsigned char *)s;
	while (++i < n)
	{
		if (*(a + i) == (unsigned char)c)
			return (a + i);
	}
	return (0);
}

// Test Main
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char s[] = "TestPlease";
	const char c = 'a';
	size_t n = 10;

	printf("%s (%s)\n", ft_memchr(s, c, n), memchr(s, c, n));

	return (0);
} */
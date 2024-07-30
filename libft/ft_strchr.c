/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:27:34 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/25 09:04:38 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	a;

	i = -1;
	a = (unsigned char)c;
	while (s[++i] != '\0')
	{
		if (s[i] == a)
			return ((char *)s + i);
	}
	if (s[i] == a)
		return ((char *)s + i);
	return ((void *)0);
}

// Test Main
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[100] = "TestPlease";

	printf("%s\n", ft_strchr(str, 'T' + 256));
} */
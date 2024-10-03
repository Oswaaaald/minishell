/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:20:56 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:47:05 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*ptr;
	unsigned char	a;

	i = -1;
	a = (unsigned char)c;
	ptr = (void *)0;
	while (s[++i] != '\0')
	{
		if (s[i] == a)
			ptr = (char *)s + i;
	}
	if (s[i] == a)
		ptr = (char *)s + i;
	return (ptr);
}

// Test Main
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[100] = "tripouille";

	printf("%s\n", ft_strrchr(str, 't' + 256));
} */
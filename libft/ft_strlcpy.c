/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:51:53 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/27 13:17:33 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		i;
	char	*crash;

	i = -1;
	if (!dst || !src)
		crash = "seg fault";
	if ((int)dstsize == -1)
		dstsize = ft_strlen(src) + 1;
	else if ((int)dstsize < 1)
		return (ft_strlen(src));
	while (src[++i] && i < (int)dstsize - 1)
	{
		dst[i] = src[i];
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// Test Main
/*
#include <string.h>

int	main(void)
{
	char	res[100];

	printf("cpy('test', 5) : %zu %s (%zu %s)\n", ft_strlcpy(res, "test", 5),
		res, strlcpy(res, "test", 5), res);
	printf("cpy('abcdef', 5) : %zu %s (%zu %s)\n", ft_strlcpy(res, "abcdef", 5),
		res, strlcpy(res, "abcdef", 5), res);
	char src[] = {'f', 'o', 'o', 'b', 'a', 'r'};
	printf("cpy(str_w/_no_null, 6) : %zu %s (%zu %s)\n", ft_strlcpy(res, src,
			6), res, strlcpy(res, src, 6), res);
	printf("cpy('fault', 10) : %zu %s (%zu %s)\n", ft_strlcpy(res, "fault", 10),
		res, strlcpy(res, "fault", 10), res);
	printf("%lu", ft_strlcpy((void *)0, (void *)0, 4));
} */

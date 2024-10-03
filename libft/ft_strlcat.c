/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:21:57 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:46:46 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	size_t			dest_len;
	size_t			src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0 && !dst)
		return (src_len);
	dest_len = ft_strlen(dst);
	i = 0;
	if (dstsize <= dest_len)
		return (src_len + dstsize);
	while (dest_len + i + 1 < dstsize && src[i])
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// Test Main
/* 
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char *dst = NULL;
	char *dst2 = NULL;
	char src[] = "abc";
	printf("cat('abc', 8) : %zu %s (%zu %s)\n", ft_strlcat(dst, src, 0), dst,
		strlcat(dst2, src, 0), dst2);
}
 */

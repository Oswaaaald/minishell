/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:42:02 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/31 11:52:40 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char const *s, size_t len)
{
	size_t	c;

	c = 0;
	while (s[c] != '\0' && len > c)
		c++;
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*ptr;

	if (!s)
		return ((void *)0);
	if ((unsigned int)ft_strlen(s) <= start)
		return (ft_strdup(""));
	ptr = (char *)s + start;
	res = (char *)malloc((int)ft_strnlen(ptr, len) + 1);
	if (!res)
		return ((void *)0);
	ft_strlcpy(res, ptr, (int)ft_strnlen(ptr, len) + 1);
	return (res);
}

// Test Main

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*str;
	size_t	start;
	size_t	size;
	char	*ret;

	str = "hola";
	start = -1;
	size = 0;
	ret = ft_substr(str, start, size);
	printf("%d\n", !strcmp(ft_substr(ret, 10, size), "") && ret);
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:42:02 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/13 17:38:36 by fghysbre         ###   ########.fr       */
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

char	*ft_substr(t_prog *prog, char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*ptr;

	if (!s)
		return ((void *)0);
	if ((unsigned int)ft_strlen(s) <= start)
		return (ft_strdup(prog, ""));
	ptr = (char *)s + start;
	res = (char *)ft_malloc(prog, (int)ft_strnlen(ptr, len) + 1);
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

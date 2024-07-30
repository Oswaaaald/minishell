/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:41:02 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/23 12:27:45 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*a;

	a = (unsigned char *)s;
	i = -1;
	while (++i < n)
		a[i] = (unsigned char)c;
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	if (dst == src)
		return (dst);
	if (!dst && !src)
		return ((void *)0);
	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	i = -1;
	while (++i < n)
		b[i] = a[i];
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	if (dst == src)
		return (dst);
	if (a < b)
	{
		while (len--)
			*(b + len) = *(a + len);
		return (dst);
	}
	while (len--)
		*b++ = *a++;
	return (dst);
}

// Test Main

/* #include <string.h>

int	main(void)
{
	int set[] = {26765656, 38758574, 15};
	int setog[] = {26765656, 38758574, 15};
	ft_memset(set, 15, 5);
	memset(setog, 15, 5);
	printf(" %d %d %d\n(%d %d %d)\n", set[0], set[1], set[2], setog[0],
		setog[1],
		setog[2]);
	int set2[] = {26765656, 38758574, 15};
	int set2og[] = {26765656, 38758574, 15};
	ft_bzero(set2, 6);
	bzero(set2og, 6);
	printf(" %d %d %d\n(%d %d %d)\n", set2[0], set2[1], set2[2], set2og[0],
		set2og[1], set2og[2]);
} */

//

/* 
int main() {
    char str[20] = "Hello, World!";
    char str2[20] = "Hello, World!";

    ft_memcpy(str + 7, str, 13);
    printf("Using memcpy: %s\n", str);
    ft_memmove(str2 + 7, str2, 13);
    printf("Using memmove: %s\n", str);

    return 0;
} */
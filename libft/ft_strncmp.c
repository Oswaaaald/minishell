/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:25:37 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/27 14:20:26 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = -1;
	if ((int)n < 1 && (int)n != -1)
		return (0);
	while (((int)n - 1 > ++i || (int)n == -1) && s1[i] && s2[i]
		&& s1[i] == s2[i])
		;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// Test Main

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char s1[] = "123";
	char s2[] = "1235";
	size_t n = -1;
	printf("%d (%d) \n", ft_strncmp(s1, s2, n), strncmp(s1, s2, n));
} */
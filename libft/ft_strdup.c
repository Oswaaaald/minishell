/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:15:26 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 14:36:55 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(t_prog *prog, const char *s1)
{
	char	*dst;
	int		i;

	dst = (char *)ft_malloc(prog, (ft_strlen(s1) + 1) * sizeof(char));
	i = -1;
	if (!dst)
		return ((void *)0);
	while (s1[++i])
		dst[i] = s1[i];
	dst[i] = '\0';
	return (dst);
}

// Test Main
/*
#include <stdio.h>

int	main(void)
{
	const char	s1[] = "TestPlease";
	char		*s2;

	s2 = ft_strdup(s1);
	printf("%s\n", s2);
	return (0);
} */

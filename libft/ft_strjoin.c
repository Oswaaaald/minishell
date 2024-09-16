/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:20:39 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 15:39:07 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)ft_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return ((void *)0);
	i = -1;
	j = -1;
	while (s1[++i] && ++j != -1)
		res[j] = s1[i];
	i = -1;
	while (s2[++i] && ++j != -1)
		res[j] = s2[i];
	res[++j] = '\0';
	return (res);
}

// Test Main
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s1;
	char	*s2;
	char	*s;

	s1 = "";
	s2 = "";
	s = ft_strjoin(s1, s2);
	printf("%d", !strcmp(s, ""));
} */

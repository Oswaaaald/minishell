/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:50:58 by fghysbre          #+#    #+#             */
/*   Updated: 2023/11/07 16:49:08 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getlen(char *start, char const *s1, char const *set)
{
	char	*end;
	int		len;

	end = (char *)s1 + ft_strlen(s1) - 1;
	while (end && ft_strchr(set, end[0]))
		end--;
	len = end - start + 1;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	char	*start;
	int		len;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	while (*start && ft_strchr(set, start[0]))
		start++;
	len = getlen(start, s1, set);
	if (len < 1)
		return (ft_strdup(""));
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return ((void *)0);
	i = 0;
	while (i < len)
	{
		res[i] = start[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// Test Main
/* 
int	main(void)
{
	printf("'%s'\n", ft_strtrim("", " \n\t"));
} */
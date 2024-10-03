/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:42:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:46:57 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		i;

	i = -1;
	if (!s || !f)
		return (NULL);
	res = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return ((void *)0);
	while (s[++i])
	{
		res[i] = f(i, s[i]);
	}
	res[i] = '\0';
	return (res);
}

// Test Main
/* 
char	test(unsigned int i, char c)
{
	if (i % 2)
		return (ft_toupper(c));
	return (c);
}

int	main(void)
{
	printf("%s\n", ft_strmapi("teststring", &test));
}
 */
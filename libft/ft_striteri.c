/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:28 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:46:41 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = -1;
	if (!s || !f)
		return ;
	while (s[++i])
	{
		f(i, &s[i]);
	}
}

// Test Main
/* 
void	test(unsigned int i, char *c)
{
	if (i % 2)
		*c = ft_toupper(*c);
}

int	main(void)
{
	char	str[] = "test";
	ft_striteri(str, test);
	printf("%s\n", str);
}
 */
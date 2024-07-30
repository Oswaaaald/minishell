/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:45:59 by fghysbre          #+#    #+#             */
/*   Updated: 2023/11/07 16:47:15 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}

// Test Main

/*
#include <string.h>

int	main(void)
{
	printf("Length of 'segmentation fault' : %d (%d) \n",
		ft_strlen("segmentation fault"), strlen("segmentation fault"));
	printf("Length of '' : %d (%d) \n",
		ft_strlen(""), strlen(""));
	char str[] = {'f', 'o', 'o'};
	printf("Length of non null terminated str : %d (%d) \n",
		ft_strlen(str), strlen(str));
}
*/
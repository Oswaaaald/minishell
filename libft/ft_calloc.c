/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:44:09 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:45:27 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size * count > UINT32_MAX)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

// Test Main
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str;

	str = (char *)ft_calloc(0, 0);
	printf("'%s'\n", str);
	str = (char *)calloc(0, 0);
	printf("'%s'\n", str);
} */
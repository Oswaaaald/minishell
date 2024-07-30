/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:32:03 by fghysbre          #+#    #+#             */
/*   Updated: 2023/11/13 11:44:51 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = -1;
	j = 0;
	if (needle && !haystack && !len)
		return (NULL);
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[++i] && i <= len)
	{
		ptr = (char *)haystack + i;
		while (haystack[i] == needle[j] && i < len)
		{
			i++;
			j++;
			if (!needle[j])
				return (ptr);
		}
		if (j)
			i = i - j;
		j = 0;
	}
	return ((void *)0);
}

/* int	main(void)
{
	ft_strnstr(NULL, "fake", 0);
} */

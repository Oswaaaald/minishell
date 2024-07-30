/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:16:54 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/16 10:24:26 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		return (c - 32);
	return (c);
}

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		return (c + 32);
	return (c);
}

// Test Main

/* #include <ctype.h>
#include <stdio.h>

const char	*getAsciiName(int asciiValue)
{
	const char *asciiNames[] = {"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK",
		"BEL", "BS ", "HT ", "LF ", "VT ", "FF ", "CR ", "SO ", "SI ", "DLE",
		"DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM ", "SUB",
		"ESC", "FS ", "GS ", "RS ", "US ", "SPC", "DEL"};
	if (asciiValue >= 0 && asciiValue <= 32)
	{
		return (asciiNames[asciiValue]);
	}
	else if (asciiValue == 127)
	{
		return (asciiNames[33]);
	}
	else
	{
		return ("");
	}
}

int	main(void)
{
	unsigned char c = 0;
	printf("ID  = upper   lower\n");
	while (c < 128)
	{
		if (getAsciiName(c)[0] != '\0')
			printf("%s = %s (%s) | %s (%s)\n", getAsciiName(c),
				getAsciiName(ft_toupper(c)), getAsciiName(toupper(c)),
				getAsciiName(ft_tolower(c)), getAsciiName(tolower(c)));
		else
			printf("%c   = %c   (%c  ) | %c   (%c  )\n",
				c, ft_toupper(c), toupper(c), ft_tolower(c), tolower(c));
		c++;
	}
} */

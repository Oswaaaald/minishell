/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:22:03 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/17 14:40:09 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else if (c > 96 && c < 123)
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}

int	ft_isalnum(int c)
{
	if (ft_isdigit(c))
		return (1);
	return (ft_isalpha(c));
}

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int	ft_isprint(int c)
{
	if (c == 32)
		return (1);
	if ((c > 32 && c < 48) || (c > 57 && c < 65) || (c > 90 && c < 97)
		|| (c > 122 && c < 127))
		return (1);
	if (ft_isdigit(c))
		return (1);
	return (ft_isalpha(c));
}

//Test Main 

/* 
#include <stdio.h>
#include <ctype.h>

const char *getAsciiName(int asciiValue) {
	const char *asciiNames[] = {
		"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
		"BS ", "HT ", "LF ", "VT ", "FF ", "CR ", "SO ", "SI ",
		"DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
		"CAN", "EM ", "SUB", "ESC", "FS ", "GS ", "RS ", "US ",
		"SPC", "DEL"
	};
	if (asciiValue >= 0 && asciiValue <= 32) {
		return asciiNames[asciiValue];
	} else if (asciiValue == 127) {
		return asciiNames[33];
	} else {
		return ("");
	}
}

int main()
{
	unsigned char   c = 0;
	printf("ID  = alpha   digit   alnum   ascii   print\n");
	while (c < 128)
	{
		if (getAsciiName(c)[0] != '\0')
			printf("%s = %d (%d) | %d (%d) | %d (%d) | %d (%d) | %d (%d)\n",
				getAsciiName(c), ft_isalpha(c), isalpha(c), ft_isdigit(c),
				isdigit(c), ft_isalnum(c), isalnum(c), ft_isascii(c),
				isascii(c), ft_isprint(c), isprint(c));
		else
			printf("%c   = %d (%d) | %d (%d) | %d (%d) | %d (%d) | %d (%d)\n",
				c, ft_isalpha(c), isalpha(c), ft_isdigit(c), isdigit(c),
				ft_isalnum(c), isalnum(c), ft_isascii(c), isascii(c),
				ft_isprint(c), isprint(c));
		c++;
	}
} */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:24:06 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:46:22 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// Test Main
/* 
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int fd = open("test.txt", O_RDWR);
	if (argc != 2)
		return (1);
	ft_putchar_fd(argv[1][0], fd);
	return (0);
} */

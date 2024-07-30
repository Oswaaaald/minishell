/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:44:19 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/31 12:10:57 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	temp;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	temp = (n % 10) + 48;
	write(fd, &temp, 1);
}

// Test Main
/* 
#include <fcntl.h>
#include <stdlib.h>

int	main(int argc, char const *argv[])
{
	int fd = open("test.txt", O_RDWR);
	if (argc != 2)
		return (1);
	ft_putnbr_fd(atoi((char *)argv[1]), 1);
	return (0);
} */
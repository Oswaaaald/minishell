/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:41:06 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:46:25 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

// Test Main
/* 
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int fd = open("test.txt", O_RDWR);
	if (argc != 2)
		return (1);
	ft_putendl_fd((char *)argv[1], fd);
	return (0);
} */

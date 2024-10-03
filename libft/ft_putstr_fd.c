/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:36:59 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:46:30 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

// Test Main

/* #include <fcntl.h>

int main(int argc, char const *argv[])
{
	int fd = open("test.txt", O_RDWR);
	if (argc != 2)
		return (1);
	ft_putstr_fd((char *)argv[1], fd);
	return (0);
} */

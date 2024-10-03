/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:00:42 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:45:25 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getsign(int i)
{
	if (i == 0)
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long int	res;
	int				i;
	int				sign;
	long long int	temp;

	i = -1;
	res = 0;
	sign = 1;
	while ((str[++i] >= 9 && str[i] <= 13) || str[i] == ' ')
		;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = (str[i] == '+');
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		temp = res;
		res = (res * 10) + getsign(sign) * (str[i] - 48);
		if ((res > temp && sign == 0) || (res < temp && sign == 1))
			return (sign * -1);
		i++;
	}
	return (res);
}

// Test Main

/* #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("%d (%d)\n", ft_atoi("-9223372036854775810999999"),
		atoi("-9223372036854775810999999"));
	return (0);
}
 */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:57:07 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/17 00:22:58 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	doexit(int	n){
	freeprog();
	exit(n);
}

int	miniexit(char **args)
{
	int	n;
	int	i;

	printf("exit\n");
	if (!args[1])
		doexit(0);
	i = -1;
	n = 0;
	while (args[1][++i])
	{
		if (i == 0 && (args[1][i] != '+' && args[1][i] != '-' &&
			!ft_isdigit(args[1][i])))
			n = 1;
		else if (i > 0 && !ft_isdigit(args[1][i]))
			n = 1;
	}
	if (n)
	{
		printf("mishell: exit: %s: numeric argument required\n", args[1]);
		doexit(2);
	}
	if (args[2])
		return(printf("bash: exit: too many arguments\n"), 1);
	doexit((char) ft_atoi(args[1]));
	return (0);
}
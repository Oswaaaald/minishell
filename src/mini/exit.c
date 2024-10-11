/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:57:07 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/11 11:06:02 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	doexit(t_prog *prog, int n)
{
	freeprog(prog);
	exit(n);
}

void	puterror(char *str)
{
	write(STDERR_FILENO, "mishell: exit: ", 15);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
}

static int	getsign(int i)
{
	if (i == 0)
		return (-1);
	return (1);
}

int	isoverflow(char	*str)
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
			return (1);
		i++;
	}
	return (0);
}

int	miniexit(t_prog *prog, char **args)
{
	int	n;
	int	i;

	printf("exit\n");
	if (!args[1])
		doexit(prog, 0);
	i = -1;
	n = 0;
	while (args[1][++i])
	{
		if ((i == 0 && (args[1][i] != '+' && args[1][i] != '-'
			&& !ft_isdigit(args[1][i]))) || (i > 0 && !ft_isdigit(args[1][i])))
			n = 1;
	}
	if (n || isoverflow(args[1]))
	{
		puterror(args[1]);
		doexit(prog, 255);
	}
	if (args[2])
		return (write(2, "bash: exit: too many arguments\n", 31), 1);
	doexit(prog, (char) ft_atoi(args[1]));
	return (0);
}

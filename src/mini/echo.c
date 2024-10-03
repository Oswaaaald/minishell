/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:36:06 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 13:41:26 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flagonlyn(char	*arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

int	miniecho(char **args)
{
	int	i;
	int	flagn;

	i = 0;
	flagn = 0;
	if (!args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	while (args[++i] && ft_strlen(args[i]) > 1 && flagonlyn(args[i]))
		flagn = 1;
	if (flagn && !args[i])
		return (1);
	i--;
	while (args[++i])
	{
		write(STDOUT_FILENO, args[i], strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!flagn)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

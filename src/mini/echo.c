/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:36:06 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/11 20:59:29 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (args[++i] && !strcmp(args[i], "-n"))
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

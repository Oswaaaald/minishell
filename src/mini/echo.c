/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:36:06 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/04 16:00:12 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	miniecho(char **args)
{
	int	i;
	int	flagn;

	i = 0;
	flagn = 0;
	while (!strcmp(args[++i], "-n"))
		flagn = 1;
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

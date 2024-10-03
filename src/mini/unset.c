/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:42:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 22:52:22 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exportputerror(int type, char c, char *s)
{
	write(STDERR_FILENO, "mishell: export: ", 17);
	if (type == 0)
	{
		write(STDERR_FILENO, "-", 1);
		write(STDERR_FILENO, &c, 1);
		write(STDERR_FILENO, ": invalid option\n", 17);
	}
	else if (type == 1)
	{
		write(STDERR_FILENO, "`", 1);
		write(STDERR_FILENO, s, ft_strlen(s));
		write(STDERR_FILENO, "': not a valid indetifier\n", 26);
	}
}

int	miniunset(char **args)
{
	int	i;
	int	togg;

	i = 0;
	togg = 0;
	while (args[++i])
	{
		if (i == 1 && !ft_strncmp(args[i], "--", -1))
			continue ;
		if (i == 1 && args[i][0] == '-')
			return (exportputerror(0, args[i][1], NULL), 2);
		else if (!nameisvalid(args[i]) || ft_strlen(args[i]) == 0)
			exportputerror(1, 0, args[i]);
		else if (ft_getenv(args[i]))
		{
			if (!ft_remenv(args[i]))
				write(STDERR_FILENO, "Warning: A malloc has failed\n", 29);
			continue ;
		}
		togg = 1;
	}
	return (togg);
}

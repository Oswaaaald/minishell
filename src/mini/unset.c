/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:42:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/07 13:29:38 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exportputerror(int cmd, int type, char c, char *s)
{
	if (cmd == 0)
		write(STDERR_FILENO, "mishell: export: ", 17);
	if (cmd == 1)
		write(STDERR_FILENO, "mishell: unset: ", 17);
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

int	miniunset(t_prog *prog, char **args)
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
			return (exportputerror(1, 0, args[i][1], NULL), 2);
		else if (!nameisvalid(args[i]) || ft_strlen(args[i]) == 0
			|| ft_strchr(args[i], '='))
			exportputerror(1, 1, 0, args[i]);
		else if (ft_getenv(prog, args[i]))
		{
			if (!ft_remenv(prog, args[i]))
				write(STDERR_FILENO, "Warning: A malloc has failed\n", 29);
			continue ;
		}
		togg = 1;
	}
	return (togg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:42:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 16:05:08 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	miniunset(char **args)
{
	int	i;
	int	togg = 1;

	i = 0;
	togg = 0;
	while (args[++i])
	{
		if (i == 1 && !ft_strncmp(args[i], "--", -1))
			i++;
		if (i == 1 && args[i][0] == '-')
			return (printf("mishell: export: -%c: invalid option\n",
					args[i][1]), 2);
		else if (!nameisvalid(args[i]))
			printf("mishell: export: %s: not a valid indetifier\n", args[i]);
		else if (ft_getenv(args[i]))
		{
			if (!ft_remenv(args[i]))
				printf("Warning: A malloc has failed");
			continue ;
		}
		togg = 1;
	}
	return (togg);
}

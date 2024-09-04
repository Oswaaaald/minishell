/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:42:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/04 16:00:23 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	miniunset(t_prog *prog, char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
			continue ;
		if (ft_getenv(prog, args[i]))
			ft_remenv(prog, args[i]);
	}
	return (1);
}

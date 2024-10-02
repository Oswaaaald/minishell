/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:43:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/02 16:59:10 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minienv(char **args)
{
	int	i;

	if (args[1])
		return (printf("mishell: env: too many arguments"), 1);
	i = -1;
	while (g_prog.minienv[++i])
	{
		if (ft_strchr(g_prog.minienv[i], '='))
			printf("%s\n", g_prog.minienv[i]);
	}
	return (1);
}

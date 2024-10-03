/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:43:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:44:27 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minienv(char **args)
{
	int	i;

	if (args[1])
		return (write(STDERR_FILENO, "mishell: env: too many arguments\n", 33)
			, 1);
	i = -1;
	while (g_prog.minienv[++i])
	{
		if (ft_strchr(g_prog.minienv[i], '='))
			printf("%s\n", g_prog.minienv[i]);
	}
	return (1);
}

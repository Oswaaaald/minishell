/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:43:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 12:48:12 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minienv(t_prog *prog, char **args)
{
	int	i;

	if (args[1])
		return (write(STDERR_FILENO, "mishell: env: too many arguments\n", 33)
			, 1);
	i = -1;
	while (prog->minienv[++i])
	{
		if (ft_strchr(prog->minienv[i], '='))
			printf("%s\n", prog->minienv[i]);
	}
	return (1);
}

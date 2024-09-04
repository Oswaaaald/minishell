/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:43:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/04 16:00:15 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minienv(t_prog *prog, char **args)
{
	int	i;

	if (args[1])
		return (printf("mishell: env: too many arguments"), 1);
	i = -1;
	while (prog->minienv[++i])
		printf("%s\n", prog->minienv[i]);
	return (1);
}

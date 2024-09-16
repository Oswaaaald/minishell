/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:43:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 16:04:06 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minienv(char **args)
{
	int	i;

	if (args[1])
		return (printf("mishell: env: too many arguments"), 1);
	i = -1;
	while (prog.minienv[++i])
		printf("%s\n", prog.minienv[i]);
	return (1);
}

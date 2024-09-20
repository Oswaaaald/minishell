/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:43:17 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/20 19:07:00 by fghysbre         ###   ########.fr       */
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
		printf("%s\n", g_prog.minienv[i]);
	return (1);
}

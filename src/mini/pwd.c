/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:37:27 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/20 19:07:00 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minipwd(void)
{
	write(STDOUT_FILENO, g_prog.cwd, strlen(g_prog.cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

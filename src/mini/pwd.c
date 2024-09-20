/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:37:27 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/20 18:24:37 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minipwd(void)
{
	write(STDOUT_FILENO, prog.cwd, strlen(prog.cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

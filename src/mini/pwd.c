/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:37:27 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 16:04:56 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minipwd()
{
	write(STDOUT_FILENO, prog.cwd, strlen(prog.cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

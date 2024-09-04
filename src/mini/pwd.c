/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:37:27 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/04 16:00:21 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minipwd(t_prog *prog)
{
	write(STDOUT_FILENO, prog->cwd, strlen(prog->cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:37:27 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/07 16:13:13 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minipwd(t_prog *prog)
{
	write(STDOUT_FILENO, prog->cwd, ft_strlen(prog->cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

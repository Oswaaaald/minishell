/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:14:34 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 22:14:56 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkerputerror(int type, char *s, int ret)
{
	write(STDERR_FILENO, "mishell: ", 9);
	ft_putstr_fd(s, STDERR_FILENO);
	if (type == 0)
		write(STDERR_FILENO, ": command not found\n", 20);
	else if (type == 1)
		write(STDERR_FILENO, ": Permission denied\n", 20);
	else if (type == 2)
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	else if (type == 3)
		write(STDERR_FILENO, ": is a directory\n", 17);
	if ((type == 0 || type == 2) && ret)
		return (127);
	else if ((type == 1 || type == 3) && ret)
		return (126);
	return (1);
}

int	isdir(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		write(2, "mishell: stat failed\n", 21);
		return (-1);
	}
	return (S_ISDIR(st.st_mode));
}

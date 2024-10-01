/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:14:34 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 22:14:47 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isdir(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		printf("mishell: stat failed");
		return (-1);
	}
	return (S_ISDIR(st.st_mode));
}

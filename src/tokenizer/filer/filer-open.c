/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer-open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:12:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/10 13:43:09 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filer.h"

int	openinput(t_cmd *cmd, char *path, int rdwr)
{
	if (cmd->fd[0] != -1)
		close(cmd->fd[0]);
	if (rdwr)
		cmd->fd[0] = open(path, O_RDWR, 0777);
	else
		cmd->fd[0] = open(path, O_RDONLY, 0777);
	return (1);
}

int	openoutput(t_cmd *cmd, char *path, int append)
{
	if (cmd->fd[1] != -1)
		close(cmd->fd[1]);
	if (append)
		cmd->fd[1] = open(path, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		cmd->fd[1] = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	return (1);
}

int	openhd(t_prog *prog, t_cmd *cmd, char *lim)
{
	if (cmd->fd[0] != -1)
		close(cmd->fd[0]);
	cmd->fd[0] = writeheredoc(prog, lim);
	if (cmd->fd[0] == -1)
		return (0);
	return (1);
}

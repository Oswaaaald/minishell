/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:24:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/08 23:17:06 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkreadfiles(t_cmd *cmd)
{
	if (cmd->input && access(cmd->input, F_OK))
		return(checkerputerror(2, cmd->input, 0), 0);
	else if (cmd->input && access(cmd->input, R_OK))
		return(checkerputerror(1, cmd->input, 0), 0);
	return (1);
}

int	checkwritefiles(t_cmd *cmd)
{
	int		tmpfd;

	if (cmd->output)
	{
		tmpfd = open(cmd->output, O_RDWR | O_CREAT, 0777);
		if (isdir(cmd->output) && checkerputerror(3, cmd->output, 0))
			return (close(tmpfd), 0);
		else if (!tmpfd)
		{
			checkerputerror(1, cmd->output, 0);
			return (0);
		}
		close(tmpfd);
	}
	return (1);
}

int	checkexecutables(t_cmd *cmd)
{
	if (checkbuiltin(cmd))
		return (0);
	if (!cmd->path)
		return (checkerputerror(0, cmd->argv[0], 1));
	else if (access(cmd->path, F_OK))
		return (checkerputerror(2, cmd->argv[0], 1));
	else if (isdir(cmd->path))
		return (checkerputerror(3, cmd->argv[0], 1));
	else if (access(cmd->path, X_OK))
		return (checkerputerror(1, cmd->argv[0], 1));
	return (0);
}

int	checkfiles(t_cmd *cmd)
{
	if (!checkreadfiles(cmd))
		return (1);
	if (!checkwritefiles(cmd))
		return (1);
	return (0);
}

int	checkcmd(t_cmd *cmd)
{
	int	status;

	status = checkexecutables(cmd);
	if (status)
		return (status);
	if (checkfiles(cmd))
		return (1);
	return (0);
}

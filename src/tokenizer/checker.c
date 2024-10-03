/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:24:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 22:27:37 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkreadfiles(t_cmdli *cmdli)
{
	int		i;
	int		togg;
	t_cmd	*cmd;

	i = -1;
	togg = 1;
	while (cmdli->cmds[++i])
	{
		cmd = cmdli->cmds[i];
		if (cmd->input && access(cmd->input, F_OK))
			checkerputerror(2, cmd->input, 0);
		else if (cmd->input && access(cmd->input, R_OK))
			checkerputerror(1, cmd->input, 0);
		else
			continue ;
		togg = 0;
	}
	return (togg);
}

int	checkwritefiles(t_cmdli	*cmdli)
{
	int		i;
	int		togg;
	t_cmd	*cmd;
	int		tmpfd;

	i = -1;
	togg = 1;
	while (cmdli->cmds[++i])
	{
		cmd = cmdli->cmds[i];
		if (cmd->output)
		{
			tmpfd = open(cmd->output, O_RDWR | O_CREAT, 0777);
			if (isdir(cmd->output) && checkerputerror(3, cmd->output, 0))
				togg = 0;
			else if (!tmpfd)
			{
				checkerputerror(1, cmd->output, 0);
				togg = 0;
				continue ;
			}
			close(tmpfd);
		}
	}
	return (togg);
}

int	checkexecutables(t_cmdli *cmdli)
{
	int		i;
	int		togg;
	t_cmd	*cmd;

	i = -1;
	togg = 0;
	while (cmdli->cmds[++i])
	{
		cmd = cmdli->cmds[i];
		if (checkbuiltin(cmd))
			continue ;
		if (!cmd->path)
			togg = checkerputerror(0, cmd->argv[0], 1);
		else if (access(cmd->path, F_OK))
			togg = checkerputerror(2, cmd->argv[0], 1);
		else if (isdir(cmd->path))
			togg = checkerputerror(3, cmd->argv[0], 1);
		else if (access(cmd->path, X_OK))
			togg = checkerputerror(1, cmd->argv[0], 1);
	}
	return (togg);
}

int	checkcmd(t_cmdli *cmdli)
{
	int	status;

	status = checkexecutables(cmdli);
	if (status)
		return (status);
	return (0);
}

int	checkfiles(t_cmdli *cmdli)
{
	if (!checkreadfiles(cmdli))
		return (1);
	if (!checkwritefiles(cmdli))
		return (1);
	return (0);
}

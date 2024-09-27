/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:24:11 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/27 19:02:27 by fghysbre         ###   ########.fr       */
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
			printf("mishell: %s: No such file or directory\n", cmd->input);
		else if (cmd->input && access(cmd->input, R_OK))
			printf("mishell: %s: Permission denied\n", cmd->input);
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
		if (cmd->input)
		{
			tmpfd = open(cmd->input, O_RDWR | O_CREAT, 0777);
			if (!tmpfd)
			{
				printf("mishell: %s: Permission denied\n", cmd->input);
				togg = 0;
			}
			else
				close(tmpfd);
		}
	}
	return (togg);
}

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

int	checkexecutables(t_cmdli *cmdli)
{
	int		i;
	int		togg;
	t_cmd	*cmd;

	i = -1;
	togg = 1;
	while (cmdli->cmds[++i])
	{
		if (checkbuiltin(cmd))
			continue ;
		cmd = cmdli->cmds[i];
		if (!cmd->path)
			printf("mishell: %s: command not found\n", cmd->argv[0]);
		else if (access(cmd->path, F_OK))
			printf("mishell: %s: No such file or directory\n", cmd->argv[0]);
		else if (access(cmd->path, X_OK))
			printf("mishell: %s: Permission denied\n", cmd->argv[0]);
		else if (isdir(cmd->path))
			printf("mishell: %s: is a directory\n", cmd->argv[0]);
		else
			continue ;
		togg = 0;
	}
	return (togg);
}

int	checkcmdli(t_cmdli *cmdli)
{
	if (!checkreadfiles(cmdli))
		return (0);
	if (!checkwritefiles(cmdli))
		return (0);
	if (!checkexecutables(cmdli))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:23:07 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/02 00:41:53 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkbuiltin(t_cmd *cmdl)
{
	if (!strcmp(cmdl->argv[0], "echo"))
		return (1);
	else if (!strcmp(cmdl->argv[0], "cd"))
		return (1);
	else if (!strcmp(cmdl->argv[0], "pwd"))
		return (1);
	else if (!strcmp(cmdl->argv[0], "env"))
		return (1);
	else if (!strcmp(cmdl->argv[0], "export"))
		return (1);
	else if (!strcmp(cmdl->argv[0], "unset"))
		return (1);
	else if (!strcmp(cmdl->argv[0], "exit"))
		return (1);
	return (0);
}

int	exebuiltin(t_cmd *cmd)
{
	if (!strcmp(cmd->argv[0], "echo"))
		return (miniecho(cmd->argv));
	else if (!strcmp(cmd->argv[0], "cd"))
		return (minicd(cmd->argv));
	else if (!strcmp(cmd->argv[0], "pwd"))
		return (minipwd());
	else if (!strcmp(cmd->argv[0], "env"))
		return (minienv(cmd->argv));
	else if (!strcmp(cmd->argv[0], "export"))
		return (miniexport(cmd->argv));
	else if (!strcmp(cmd->argv[0], "unset"))
		return (miniunset(cmd->argv));
	else if (!strcmp(cmd->argv[0], "exit"))
		return (miniexit(cmd->argv));
	return (1);
}

void	cmdbuiltin(t_cmdli *cmdli, int i)
{
	t_cmd	*cmd;

	cmd = cmdli->cmds[i];
	if (cmd->output)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->input || cmd->limmiter)
		dup2(cmd->fd[0], STDIN_FILENO);
	g_prog.lastexit = exebuiltin(cmd);
}

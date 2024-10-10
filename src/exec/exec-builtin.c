/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:23:07 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/10 14:07:07 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkbuiltin(t_cmd *cmdl)
{
	if (!cmdl->argv[0])
		return (0);
	if (!ft_strncmp(cmdl->argv[0], "echo", -1))
		return (1);
	else if (!ft_strncmp(cmdl->argv[0], "cd", -1))
		return (1);
	else if (!ft_strncmp(cmdl->argv[0], "pwd", -1))
		return (1);
	else if (!ft_strncmp(cmdl->argv[0], "env", -1))
		return (1);
	else if (!ft_strncmp(cmdl->argv[0], "export", -1))
		return (1);
	else if (!ft_strncmp(cmdl->argv[0], "unset", -1))
		return (1);
	else if (!ft_strncmp(cmdl->argv[0], "exit", -1))
		return (1);
	return (0);
}

int	exebuiltin(t_prog *prog, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->argv[0], "echo", -1))
		return (miniecho(cmd->argv));
	else if (!ft_strncmp(cmd->argv[0], "cd", -1))
		return (minicd(prog, cmd->argv));
	else if (!ft_strncmp(cmd->argv[0], "pwd", -1))
		return (minipwd(prog));
	else if (!ft_strncmp(cmd->argv[0], "env", -1))
		return (minienv(prog, cmd->argv));
	else if (!ft_strncmp(cmd->argv[0], "export", -1))
		return (miniexport(prog, cmd->argv));
	else if (!ft_strncmp(cmd->argv[0], "unset", -1))
		return (miniunset(prog, cmd->argv));
	else if (!ft_strncmp(cmd->argv[0], "exit", -1))
		return (miniexit(prog, cmd->argv));
	return (1);
}

int	cmdbuiltin(t_prog *prog, t_cmdli *cmdli, int i)
{
	t_cmd	*cmd;
	int		tmp;

	cmd = cmdli->cmds[i];
	tmp = -2;
	if (cmd->output)
		tmp = dup2(cmd->fd[1], STDOUT_FILENO);
	if (tmp == -1)
		return (0);
	if (cmd->input || cmd->limmiter)
		tmp = dup2(cmd->fd[0], STDIN_FILENO);
	if (tmp == -1)
		return (0);
	g_interupt = exebuiltin(prog, cmd);
	return (1);
}

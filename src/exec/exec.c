/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:20:27 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/08 23:16:33 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dupfds(t_cmdli *cmdli, int pfd[2], int i, int prev_fd)
{
	t_cmd	*cmd;
	int		tmp;

	cmd = cmdli->cmds[i];
	tmp = 0;
	if (cmd->limmiter || cmd->input)
		tmp = dup2(cmd->fd[0], STDIN_FILENO);
	else if (i && prev_fd != -1)
		tmp = dup2(prev_fd, STDIN_FILENO);
	if (tmp == -1)
		return (0);
	if (cmd->output)
		tmp = dup2(cmd->fd[1], STDOUT_FILENO);
	else if (cmdli->cmds[i + 1])
		tmp = dup2(pfd[1], STDOUT_FILENO);
	if (tmp == -1)
		return (0);
	return (1);
}

void	cmdchild(t_prog *prog, t_cmdli *cmdli, int pipes[2], int i[2])
{
	t_cmd	*cmd;
	int		tmp;

	cmd = cmdli->cmds[i[0]];
	tmp = checkcmd(cmd);
	if (tmp)
		exit(tmp);
	if (!dupfds(cmdli, pipes, i[0], i[1]))
		exit(EXIT_FAILURE);
	closefd(cmd->fd);
	closefd(pipes);
	if (!checkbuiltin(cmd))
	{
		if (execve(cmd->path, cmd->argv, prog->minienv))
			exit(EXIT_FAILURE);
	}
	else
		exit(exebuiltin(prog, cmd));
}

int	cmd(t_prog *prog, t_cmdli *cmdli, int i)
{
	pid_t		pid;
	t_cmd		*cmd;
	static int	prev_fd;
	int			pipes[2];

	cmd = cmdli->cmds[i];
	if (i == 0)
		prev_fd = -1;
	if (pipe(pipes) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (closefd(pipes), 0);
	if (!pid)
		cmdchild(prog, cmdli, pipes, (int [2]){i, prev_fd});
	if (!cmdli->cmds[i + 1] && pid > 0)
		cmdli->lastpid = pid;
	cmd->pid = pid;
	if (i != 0)
		close(prev_fd);
	prev_fd = pipes[0];
	close(pipes[1]);
	return (1);
}

void	hdchild(t_prog *prog, char *lim, int fd[2])
{
	char	*buff;
	char	*tmp;

	close(fd[0]);
	signal(SIGINT, sigheredoc);
	while (1)
	{
		buff = readline("> ");
		if (!buff)
			exit(EXIT_SUCCESS);
		tmp = expandstr(prog, buff);
		if (!tmp)
			exit(EXIT_FAILURE);
		if (ft_strncmp(buff, lim, -1) == 0)
			break ;
		ft_free(prog, buff);
		write(fd[1], tmp, ft_strlen(tmp));
		write(fd[1], "\n", 1);
		ft_free(prog, tmp);
	}
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

int	writeheredoc(t_prog *prog, char *lim)
{
	int		fd[2];
	int		ret;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	ret = 0;
	g_interupt = ST_HEDOC;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		hdchild(prog, lim, fd);
	close(fd[1]);
	wait(&ret);
	if (ret)
		return (-1);
	return (fd[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:20:27 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/02 00:19:00 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dupfds(t_cmdli *cmdli, int pfd[2], int i, int prev_fd)
{
	t_cmd	*cmd;

	cmd = cmdli->cmds[i];
	if (cmd->limmiter || cmd->input)
		dup2(cmd->fd[0], STDIN_FILENO);
	else if (i && prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->output)
		dup2(cmd->fd[1], STDOUT_FILENO);
	else if (cmdli->cmds[i + 1])
		dup2(pfd[1], STDOUT_FILENO);
}

void	cmdchild(t_cmdli *cmdli, int pipes[2], int i, int prev_fd)
{
	t_cmd	*cmd;

	cmd = cmdli->cmds[i];
	dupfds(cmdli, pipes, i, prev_fd);
	closefd(cmd->fd);
	closefd(pipes);
	if (!checkbuiltin(cmd))
	{
		if (execve(cmd->path, cmd->argv, g_prog.minienv))
			exit(EXIT_FAILURE);
	}
	else
		exit(exebuiltin(cmd));
}

int	cmd(t_cmdli *cmdli, int i)
{
	pid_t		pid;
	t_cmd		*cmd;
	static int	prev_fd;
	int			pipes[2];

	cmd = cmdli->cmds[i];
	if (i == 0)
		prev_fd = -1;
	pipe(pipes);
	pid = fork();
	if (!pid)
		cmdchild(cmdli, pipes, i, prev_fd);
	if (!cmdli->cmds[i + 1] && pid > 0)
		cmdli->lastpid = pid;
	cmd->pid = pid;
	if (i != 0)
		close(prev_fd);
	prev_fd = pipes[0];
	close(pipes[1]);
	return (1);
}

void	hdchild(char *lim, int fd[2])
{
	char	*buff;

	close(fd[0]);
	signal(SIGINT, sigheredoc);
	while (1)
	{
		buff = readline("> ");
		if (!buff)
			exit(EXIT_FAILURE);
		if (strcmp(buff, lim) == 0)
			break ;
		write(fd[1], buff, strlen(buff));
		write(fd[1], "\n", 1);
		ft_free(buff);
	}
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

int	writeheredoc(char *lim)
{
	int		fd[2];
	int		ret;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	ret = 0;
	g_prog.status = ST_HEDOC;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		hdchild(lim, fd);
	close(fd[1]);
	wait(&ret);
	g_prog.status = ST_IDLE;
	if (ret)
		return (-1);
	return (fd[0]);
}

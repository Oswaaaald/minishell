/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:42:03 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/11 22:23:53 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closefd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	setstatus(t_prog *prog, int status)
{
	if (WIFEXITED(status))
		prog->lastexit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		prog->lastexit = WTERMSIG(status) + 128;
}

int	writeheredoc(char *lim)
{
	char	*buff;
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			buff = readline("> ");
			if (strcmp(buff, lim) == 0)
				break ;
			write(fd[1], buff, strlen(buff));
			write(fd[1], "\n", 1);
			free(buff);
		}
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	wait(0);
	dup2(fd[0], STDIN_FILENO);
	return (1);
}

int	*openfd(t_cmd *cmd)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	if (pipe(fd) == -1)
		return (NULL);
	if (cmd->input)
	{
		close(fd[0]);
		fd[0] = open(cmd->input, O_RDONLY, 0777);
		if (fd[0] == -1)
			return (closefd(fd), NULL);
	}
	if (cmd->output)
	{
		close(fd[1]);
		if (cmd->outappend)
			fd[1] = open(cmd->output, O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			fd[1] = open(cmd->output, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd[1] == -1)
			return (closefd(fd), NULL);
	}
	return (fd);
}

int	cmd(t_cmdli *cmdli, int i)
{
	int		*fd;
	pid_t	pid;
	t_cmd	*cmd;

	cmd = cmdli->cmds[i];
	fd = openfd(cmd);
	if (!fd)
		return (0);
	if (cmd->limmiter)
		writeheredoc(cmd->limmiter);
	pid = fork();
	if (!cmdli->cmds[i + 1] && pid > 0)
		cmdli->lastpid = pid;
	if (!pid)
	{
		if (!cmdli->cmds[i + 1] && !cmd->output)
			dup2(STDOUT_FILENO, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		if (execve(cmd->path, cmd->argv, cmd->env))
			return (0);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	return (1);
}

int	exebuiltin(t_prog *prog, t_cmd *cmd)
{
	if (!strcmp(cmd->argv[0], "echo"))
		return (miniecho(cmd->argv));
	else if (!strcmp(cmd->argv[0], "cd"))
		return (minicd(prog, cmd->argv));
	else if (!strcmp(cmd->argv[0], "pwd"))
		return (minipwd(prog));
	else if (!strcmp(cmd->argv[0], "env"))
		return (minienv(prog, cmd->argv));
	else if (!strcmp(cmd->argv[0], "export"))
		return (miniexport(prog, cmd->argv));
	else if (!strcmp(cmd->argv[0], "unset"))
		return (miniunset(prog, cmd->argv));
	return (1);
}

void	cmdbuiltin(t_prog *prog, t_cmdli *cmdli, int i)
{
	int		*fd;
	t_cmd	*cmd;

	cmd = cmdli->cmds[i];
	fd = openfd(cmd);
	if (cmd->output)
		dup2(fd[1], STDOUT_FILENO);
	if (cmd->input)
		dup2(fd[0], STDIN_FILENO);
	prog->lastexit = exebuiltin(prog, cmd);
}

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
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_prog	prog;
	int		i;
	t_cmdli	*cmdli;
	char	*line;
	int		is_builtin;

	if (!argc && !argv && !envp)
		return (1);
	if (!initprog(&prog, envp))
		return (printf("mishell: Init error\n"));
	while (1)
	{
		line = readline("mishell> ");
		if (!line)
			break ;
		if (!*line)
		{
			free(line);
			continue ;
		}
		if (!strcmp(line, "exit"))
		{
			free(line);
			return (0);
		}
		cmdli = tokenize(&prog, line);
		free(line);
		if (!cmdli)
			return (0);
		i = 0;
		while (i < cmdli->nbcmds)
		{
			is_builtin = checkbuiltin(cmdli->cmds[i]);
			if (is_builtin)
			{
				cmdli->cmds[i]->path = "BUILTIN";
				cmdbuiltin(&prog, cmdli, i);
			}
			else
			{
				// Corriger cette ligne avec le bon path
				cmdli->cmds[i]->path
					= parsepath(&prog, cmdli->cmds[i]->argv[0]);
				if (!cmdli->cmds[i]->path)
					return (0);
				if (!cmd(cmdli, i))
					return (0);
			}
			i++;
		}
		// Print path
		printf("PATH: %s\n", cmdli->cmds[0]->path);
		i = 0;
		while (i < cmdli->nbcmds)
			free(cmdli->cmds[i++]);
		free(cmdli->cmds);
		free(cmdli);
	}
	return (0);
}

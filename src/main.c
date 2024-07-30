/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:42:03 by codespace         #+#    #+#             */
/*   Updated: 2024/07/30 17:05:58 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closefd(int fd[2])
{
		close(fd[0]);
		close(fd[1]);
}

void	setStatus(t_prog *prog, int status)
{
	if (WIFEXITED(status))
		prog->lastExit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		prog->lastExit = WTERMSIG(status) + 128;
}

int	writeheredoc(char *lim)
{
	char	*buff;
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return 0;
	pid = fork();
	if (pid == -1)
		return 0;
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
	return 1;
}

int	*openfd(t_cmd *cmd) {
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

int cmd(t_cmdli *cmdli, int i) {
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
		cmdli->lastPid = pid;
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

void	cmdBuiltin(t_prog *prog, t_cmdli *cmdli, int i)
{
	int		*fd;
	t_cmd	*cmd;

	cmd = cmdli->cmds[i];
	fd = openfd(cmd);
	if (cmd->output)
		dup2(fd[1], STDOUT_FILENO);
	if (cmd->input)
		dup2(fd[0], STDIN_FILENO);
	if (!strcmp(cmd->argv[0], "echo"))
		miniecho(cmd->argv);
	else if(!strcmp(cmd->argv[0], "cd"))
		minicd(prog, cmd->argv);
	else if(!strcmp(cmd->argv[0], "pwd"))
		minipwd();
}

void	initenv(t_prog *prog)
{
	int i;

	i = 0;
	while (environ[i])
		i++;
	prog->envmod = ft_calloc(i, sizeof(int));
}

int main(int argc, char **argv, char **envp)
{
	t_prog	prog;
	/* t_cmdli **cmdli;
	int		status; */

	if (!argc && !argv && !envp)
		return (1);
	initenv(&prog);
	char *temp[] = {"export", NULL};
	miniexport(temp);
	//minipwd();
	/* cmdli = malloc(sizeof(t_cmdli* ) * 3);
	cmdli[0] = malloc(sizeof(t_cmdli));
	cmdli[0]->cmds = malloc(sizeof(t_cmd *) * 4);
	cmdli[0]->cmds[0] = malloc(sizeof(t_cmd));
	cmdli[0]->cmds[0]->path = "builtin";
	cmdli[0]->cmds[0]->argv = malloc(sizeof(char *) * 6);
	cmdli[0]->cmds[0]->argv[0] = "cd";
	cmdli[0]->cmds[0]->argv[1] = "~";
	cmdli[0]->cmds[0]->argv[2] = NULL;
	cmdli[0]->cmds[0]->argv[3] = "test";
	cmdli[0]->cmds[0]->argv[4] = "-n";
	cmdli[0]->cmds[0]->argv[5] = NULL;
	cmdli[0]->cmds[0]->env = malloc(sizeof(char *) * 1);
	cmdli[0]->cmds[0]->env[0] = NULL;
	cmdli[0]->cmds[0]->input = NULL;
	cmdli[0]->cmds[0]->output = NULL;
	cmdli[0]->cmds[0]->limmiter = NULL;
	cmdli[0]->cmds[0]->outappend = 0;
	cmdli[0]->cmds[1] = NULL;
	cmdli[1] = NULL; */

	/* for (int i = 0; cmdli[i]; i++) {
		if (cmdli[i]->cmds[1] == NULL && !strcmp(cmdli[i]->cmds[0]->path, "builtin"))
		{
			cmdBuiltin(cmdli[i], 0);
			continue;
		}
		for (int j = 0; cmdli[i]->cmds[j]; j++) {
			cmd(cmdli[i], j);
		}
		for (int j = 0; cmdli[i]->cmds[j]; j++) {
			pid_t pid = wait(&status);
			if (pid == cmdli[i]->lastPid)
				setStatus(&prog, status);
			printf("status: %d (%d ?= %d)\n", status, pid, cmdli[i]->lastPid);
		}
		dup2(STDIN_FILENO, STDIN_FILENO);
		if (prog.lastExit > 0)
			break ;
	} */
}
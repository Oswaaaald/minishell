/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:42:03 by codespace         #+#    #+#             */
/*   Updated: 2024/07/18 14:21:29 by codespace        ###   ########.fr       */
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

void	miniecho(t_cmd *cmd, char **args)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (args[++i]) {
		write(STDOUT_FILENO, args[i], strlen(args[i]));
	}
	return ;
}

char	*strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(strlen(s1) + strlen(s2) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	i--;
	j = -1;
	while (s2[++j] && ++i)
		ret[i] = s2[j];
	ret[i + 1] = '\0';
	return (ret);
}

char	*pathparse(char *path)
{
	char	*home;
	char 	*ret;
	if (path[0] == '~' && (path[1] == '/' || !path[1]))
	{
		home = getenv("HOME");
		ret = strjoin(home, path + 1);
		return (ret);
	}
	return (strjoin(path, ""));
}

void	minicd(t_cmd *cmd, char **args)
{
	char	*buff;

	if (!cmd)
		return ;
	if (args[2] != NULL)
	{
		write(STDERR_FILENO, "mishell: cd: too many arguments\n", 33);
		return ;
	}
	else if (args[1] == NULL)
		buff = pathparse("~");
	else
		buff = pathparse(args[1]);
	if (chdir(buff) == -1 && errno == ENOENT)
		perror("mishell: cd: ");
	printf("%s\n", buff);
	free(buff);
}

void	cmdBuiltin(t_cmdli *cmdli, int i)
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
		miniecho(cmd, cmd->argv);
	else if(!strcmp(cmd->argv[0], "cd"))
		minicd(cmd, cmd->argv);
}

int main(int argc, char **argv, char **envp)
{
	t_prog	prog;
	t_cmdli **cmdli;
	int		status;

	if (!argc && !argv && !envp)
		return (1);
	getcwd(prog.cwd, 256);
	printf("%s\n", prog.cwd);
	cmdli = malloc(sizeof(t_cmdli* ) * 3);
	cmdli[0] = malloc(sizeof(t_cmdli));
	cmdli[0]->cmds = malloc(sizeof(t_cmd *) * 4);
	cmdli[0]->cmds[0] = malloc(sizeof(t_cmd));
	cmdli[0]->cmds[0]->path = "builtin";
	cmdli[0]->cmds[0]->argv = malloc(sizeof(char *) * 3);
	cmdli[0]->cmds[0]->argv[0] = "cd";
	cmdli[0]->cmds[0]->argv[1] = "~/19s";
	cmdli[0]->cmds[0]->argv[2] = NULL;
	cmdli[0]->cmds[0]->env = malloc(sizeof(char *) * 1);
	cmdli[0]->cmds[0]->env[0] = NULL;
	cmdli[0]->cmds[0]->input = NULL;
	cmdli[0]->cmds[0]->output = NULL;
	cmdli[0]->cmds[0]->limmiter = NULL;
	cmdli[0]->cmds[0]->outappend = 0;
	cmdli[0]->cmds[1] = malloc(sizeof(t_cmd));
	cmdli[0]->cmds[1]->path = "/usr/bin/grep";
	cmdli[0]->cmds[1]->argv = malloc(sizeof(char *) * 3);
	cmdli[0]->cmds[1]->argv[0] = "grep";
	cmdli[0]->cmds[1]->argv[1] = "hello";
	cmdli[0]->cmds[1]->argv[2] = NULL;
	cmdli[0]->cmds[1]->env = malloc(sizeof(char *) * 1);
	cmdli[0]->cmds[1]->env[0] = NULL;
	cmdli[0]->cmds[1]->input = NULL;
	cmdli[0]->cmds[1]->output = NULL;
	cmdli[0]->cmds[1]->limmiter = NULL;
	cmdli[0]->cmds[1]->outappend = 0;
	cmdli[0]->cmds[2] = malloc(sizeof(t_cmd));
	cmdli[0]->cmds[2]->path = "/usr/bin/false";
	cmdli[0]->cmds[2]->argv = malloc(sizeof(char *) * 3);
	cmdli[0]->cmds[2]->argv[0] = "false";
	cmdli[0]->cmds[2]->argv[1] = NULL;
	cmdli[0]->cmds[2]->argv[2] = NULL;
	cmdli[0]->cmds[2]->env = malloc(sizeof(char *) * 1);
	cmdli[0]->cmds[2]->env[0] = NULL;
	cmdli[0]->cmds[2]->input = NULL;
	cmdli[0]->cmds[2]->output = NULL;
	cmdli[0]->cmds[2]->limmiter = NULL;
	cmdli[0]->cmds[2]->outappend = 0;
	cmdli[0]->cmds[3] = NULL;
	cmdli[0]->cmds[1] = NULL;
	cmdli[1] = malloc(sizeof(t_cmdli));
	cmdli[1]->cmds = malloc(sizeof(t_cmd *) * 2);
	cmdli[1]->cmds[0] = malloc(sizeof(t_cmd));
	cmdli[1]->cmds[0]->path = "/usr/bin/echo";
	cmdli[1]->cmds[0]->argv = malloc(sizeof(char *) * 3);
	cmdli[1]->cmds[0]->argv[0] = "echo";
	cmdli[1]->cmds[0]->argv[1] = "success";
	cmdli[1]->cmds[0]->argv[2] = NULL;
	cmdli[1]->cmds[0]->env = malloc(sizeof(char *) * 1);
	cmdli[1]->cmds[0]->env[0] = NULL;
	cmdli[1]->cmds[0]->input = NULL;
	cmdli[1]->cmds[0]->output = NULL;
	cmdli[1]->cmds[0]->limmiter = NULL;
	cmdli[1]->cmds[0]->outappend = 0;
	cmdli[1]->cmds[1] = NULL;
	cmdli[1] = NULL;
	cmdli[2] = NULL;

	for (int i = 0; cmdli[i]; i++) {
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
	}

	getcwd(prog.cwd, 256);
	printf("%s\n", prog.cwd);
}
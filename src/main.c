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

int	writeheredoc(char *lim)
{
	char	*buff;
	char	pid;
	int		fd[2];

	pid = fork();
	if (pipe(fd) == -1)
		return (0);
	if (!pid)
	{
		close(fd[0]);
		while (1)
		{
			buff = readline("> ");
			if (strcmp(buff, lim) == 0)
			{
				printf("%d\n", strcmp(buff, lim));
				break ;
			}
			write(fd[1], buff, strlen(buff));
			free(buff);
			buff = NULL;
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(0);
		printf("done");
		printf("%s\n", strerror(errno));
	}
	return (1);
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
	pid = fork();
	if (cmd->limmiter)
		writeheredoc(cmd->limmiter);
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

int main(int argc, char **argv, char **envp)
{
	//t_prog	prog;
	t_cmdli cmdli;

	if (!argc && !argv && !envp)
		return (1);
	cmdli.cmds = malloc(sizeof(t_cmd *) * 3);
	cmdli.cmds[0] = malloc(sizeof(t_cmd));
	cmdli.cmds[0]->path = "/usr/bin/cat";
	cmdli.cmds[0]->argv = malloc(sizeof(char *) * 3);
	cmdli.cmds[0]->argv[0] = "cat";
	cmdli.cmds[0]->argv[1] = NULL;
	cmdli.cmds[0]->argv[2] = NULL;
	cmdli.cmds[0]->env = malloc(sizeof(char *) * 1);
	cmdli.cmds[0]->env[0] = NULL;
	cmdli.cmds[0]->input = NULL;
	cmdli.cmds[0]->output = NULL;
	cmdli.cmds[0]->limmiter = "thong";
	cmdli.cmds[0]->outappend = 0;
	/* cmdli.cmds[1] = malloc(sizeof(t_cmd));
	cmdli.cmds[1]->path = "/usr/bin/wc";
	cmdli.cmds[1]->argv = malloc(sizeof(char *) * 3);
	cmdli.cmds[1]->argv[0] = "wc";
	cmdli.cmds[1]->argv[1] = "-l";
	cmdli.cmds[1]->argv[2] = NULL;
	cmdli.cmds[1]->env = malloc(sizeof(char *) * 1);
	cmdli.cmds[1]->env[0] = NULL;
	cmdli.cmds[1]->input = NULL;
	cmdli.cmds[1]->output = NULL;
	cmdli.cmds[1]->limmiter = NULL;
	cmdli.cmds[1]->outappend = 0; */
	cmdli.cmds[1] = NULL;
	cmdli.cmds[2] = NULL;

	for (int i = 0; cmdli.cmds[i]; i++) {
		cmd(&cmdli, i);
	}
}
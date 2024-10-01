/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:42:03 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 17:31:40 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closefd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	setstatus(int status)
{
	if (WIFEXITED(status))
		g_prog.lastexit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_prog.lastexit = WTERMSIG(status) + 128;
}

//TODO: add handle when ctrl+C mid heredoc and move heredoc to execute before any command
int	writeheredoc(char *lim)
{
	char	*buff;
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
	{
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
	close(fd[1]);
	wait(&ret);
	g_prog.status = ST_IDLE;
	if (ret)
		return (-1);
	return (fd[0]);
}

int	openfd(t_cmd *cmd)
{
	int	*fd;

	fd = cmd->fd;
	if (pipe(fd) == -1)
		return (0);
	if (cmd->input)
	{
		close(fd[0]);
		fd[0] = open(cmd->input, O_RDONLY, 0777);
		if (fd[0] == -1)
			return (closefd(fd), 0);
	}
	if (cmd->limmiter)
	{
		close(fd[0]);
		fd[0] = writeheredoc(cmd->limmiter);
		if (fd[0] == -1)
			return (closefd(fd), 0);
	}
	if (cmd->output)
	{
		close(fd[1]);
		if (cmd->outappend)
			fd[1] = open(cmd->output, O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			fd[1] = open(cmd->output, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd[1] == -1)
			return (closefd(fd), 0);
	}
	return (1);
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

void	dupfds(t_cmdli *cmdli, int	pfd[2], int i, int prev_fd)
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

int	cmd(t_cmdli *cmdli, int i/* , int prev_fd */)
{
	pid_t		pid;
	t_cmd		*cmd;
	static int	prev_fd;
	int			pipes[2];

	cmd = cmdli->cmds[i];
	if (i == 0)
		prev_fd = -1;/* 
	if (!openfd(cmd))
		return (0); */
	pipe(pipes);
	pid = fork();
	if (!pid)
	{
		/* if (cmdli->cmds[i + 1] || cmd->output)
			dup2(cmd->fd[1], STDOUT_FILENO);
		if (prev_fd && (i || cmd->input || cmd->limmiter))
			dup2(prev_fd, STDIN_FILENO); */
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
	if (!cmdli->cmds[i + 1] && pid > 0)
		cmdli->lastpid = pid;
	cmd->pid = pid;
	if (i != 0)
		close(prev_fd);
	prev_fd = pipes[0];
	// if (i && cmdli->cmds[i + 1])
	// 	dup2(cmd->fd[0], STDIN_FILENO);
	//if (i != cmdli->nbcmds - 1)
		close(pipes[1]);/* 
	if (i != 0)
		close(prev_fd); */
	return (1);
}

void	cmdbuiltin(t_cmdli *cmdli, int i)
{
	t_cmd	*cmd;

	cmd = cmdli->cmds[i];
	if (!openfd(cmd))
		return ;
	if (cmd->output)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->input)
		dup2(cmd->fd[0], STDIN_FILENO);
	g_prog.lastexit = exebuiltin(cmd);
}

void	freeprog(void)
{
	t_list	*tmp;
	t_list	*crnt;

	crnt = g_prog.mallocs;
	while (crnt)
	{
		tmp = crnt->next;
		if (crnt->content)
			free(crnt->content);
		free(crnt);
		crnt = tmp;
	}
	//rl_clear_history();
}

char	*ft_readline(void)
{
	char	*home;
	char	*buff;
	char	*ret;

	home = ft_getenv("HOME");
	buff = NULL;
	if (home && !ft_strncmp(home, g_prog.cwd, ft_strlen(home)))
	{
		home = ft_strjoin("~", g_prog.cwd + ft_strlen(home));
		if (!home)
			return (NULL);
		buff = ft_strjoin("\033[32;1mmishell\033[0m:\033[34;1m", home);
		ft_free(home);
	}
	else
		buff = ft_strjoin("\033[32;1mmishell\033[0m:\033[34;1m", g_prog.cwd);
	if (!buff)
		return (NULL);
	home = ft_strjoin(buff, "\033[0m$ ");
	ft_free(buff);
	if (!home)
		return (NULL);
	ret = readline(home);
	ft_malloc_add_ptr(ret);
	ft_free(home);
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	*line;
	int		stds[2];
	int		togg;

	if (!argc && !argv && !envp)
		return (1);
	if (!initprog(envp))
		return (printf("mishell: Init error\n"));
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	//char temp[10];
	while (1)
	{
		g_prog.interupt = 0;
		g_prog.cmdli = NULL;
		//printf("%ld\n", read(STDIN_FILENO, temp, 10));
		//perror(strerror(errno));
		stds[0] = dup(STDIN_FILENO);
		stds[1] = dup(STDOUT_FILENO);
		line = ft_readline();
		if (!line)
			return (printf("exit\n"), freeprog(), 0);
		if (!*line)
		{
			ft_free(line);
			continue ;
		}
		g_prog.cmdli = tokenize(line);
		if (!g_prog.cmdli)
		{
			closefd(stds);
			continue ;
		}
		i = -1;
		togg = 0;
		while (++i < g_prog.cmdli->nbcmds)
		{
			if (!openfd(g_prog.cmdli->cmds[i]))
			{
				closefd(stds);
				while (i < g_prog.cmdli->nbcmds)
					ft_free(g_prog.cmdli->cmds[i++]);
				ft_free(g_prog.cmdli->cmds);
				ft_free(g_prog.cmdli);
				togg = 1;
				break ;
			}
		}
		if (togg)
			continue ;
		i = 0;
		//int	prev_fd;
		//prev_fd = 0;
		g_prog.status = ST_RUN;
		while (i < g_prog.cmdli->nbcmds)
		{
			if (checkbuiltin(g_prog.cmdli->cmds[i])
				&& g_prog.cmdli->nbcmds == 1)
			{
				g_prog.cmdli->cmds[i]->path = "BUILTIN";
				cmdbuiltin(g_prog.cmdli, i);
			}
			else
			{
				/* if (i == 0 && !(g_prog.cmdli->cmds[i]->input || g_prog.cmdli->cmds[i]->limmiter))
					close(g_prog.cmdli->cmds[0]->fd[0]);
				else */ //if (i == 0)
					//prev_fd = g_prog.cmdli->cmds[0]->fd[0];
				//openfd(g_prog.cmdli->cmds[i]);
				if (!cmd(g_prog.cmdli, i/* , prev_fd */))
					return (0);
				/* if (i != g_prog.cmdli->nbcmds - 1)
					close(g_prog.cmdli->cmds[i]->fd[1]); */
				//prev_fd = g_prog.cmdli->cmds[i]->fd[0];
			}
			i++;
		}
		// Print path
		//printf("PATH: %s\n", g_prog.cmdli->cmds[0]->path);
		for (int j = 0; j < i; j++) {
			int	status;
			waitpid(g_prog.cmdli->cmds[j]->pid, &status, 0);
			if (g_prog.cmdli->cmds[j]->pid == g_prog.cmdli->lastpid)
				setstatus(status);
		}
		for (int j = 0; j < i; j++) {
			closefd(g_prog.cmdli->cmds[j]->fd);
		}
		if (g_prog.interupt && g_prog.lastexit)
			printf("\n");
		g_prog.status = ST_IDLE;
		i = 0;
		dup2(stds[0], STDIN_FILENO);
		dup2(stds[1], STDOUT_FILENO);
		close(stds[0]);
		close(stds[1]);
		while (i < g_prog.cmdli->nbcmds)
			ft_free(g_prog.cmdli->cmds[i++]);
		ft_free(g_prog.cmdli->cmds);
		ft_free(g_prog.cmdli);
	}
	return (0);
}

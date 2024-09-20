/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:42:03 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/20 18:29:42 by mleonet          ###   ########.fr       */
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
		prog.lastexit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		prog.lastexit = WTERMSIG(status) + 128;
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
			ft_malloc_add_ptr(buff);
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
	wait(0);
	dup2(fd[0], STDIN_FILENO);
	return (1);
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

int	cmd(t_cmdli *cmdli, int i)
{
	pid_t		pid;
	t_cmd		*cmd;
	static int	prev_fd;

	cmd = cmdli->cmds[i];
	// prev_fd = 0;
	if (i == 0)
		prev_fd = cmdli->cmds[0]->fd[0];
	if (!openfd(cmd))
		return (0);
	if (cmd->limmiter)
		writeheredoc(cmd->limmiter);
	pid = fork();
	if (!pid)
	{
		if (cmdli->cmds[i + 1] || cmd->output)
			dup2(cmd->fd[1], STDOUT_FILENO);
		if (i)
			dup2(prev_fd, STDIN_FILENO);
		closefd(cmd->fd);
		if (!checkbuiltin(cmd))
		{
			if (execve(cmd->path, cmd->argv, prog.minienv))
				exit(EXIT_FAILURE);
		}
		else
			exit(exebuiltin(cmd));
	}
	if (!cmdli->cmds[i + 1] && pid > 0)
		cmdli->lastpid = pid;
	cmd->pid = pid;
	if (prev_fd != 0)
		close(prev_fd);
	prev_fd = cmd->fd[0];
	// if (i && cmdli->cmds[i + 1])
	// 	dup2(cmd->fd[0], STDIN_FILENO);
	close(cmd->fd[1]);
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
	prog.lastexit = exebuiltin(cmd);
}

char	**getpaths(char **env)
{
	int		i;
	char	*pathe;
	char	**res;

	i = -1;
	pathe = NULL;
	while (env[++i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			pathe = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	}
	if (!pathe)
		return (NULL);
	res = ft_split(pathe, ':');
	ft_free(pathe);
	if (!res)
		return (NULL);
	return (res);
}

char	*pather(char *cmd)
{
	char	*buffer;
	char	**paths;
	char	*tmpcmd;
	int		i;

	if (ft_strchr("/.~", cmd[0]))
		return (parsepath(cmd));
	tmpcmd = ft_strjoin("/", cmd);
	if (!tmpcmd)
		return (NULL);
	paths = getpaths(prog.minienv);
	if (!paths)
		return (ft_free(tmpcmd), NULL);
	i = -1;
	while (paths[++i])
	{
		buffer = ft_strjoin(paths[i], tmpcmd);
		if (!buffer)
			return (ft_free(tmpcmd), free2d(paths), NULL);
		if (access(buffer, X_OK) == 0)
			return (ft_free(tmpcmd), free2d(paths), buffer);
		ft_free(buffer);
	}
	ft_free(tmpcmd);
	free2d(paths);
	return (NULL);
}

void	freeprog(void)
{
	t_list	*tmp;
	t_list	*crnt;

	crnt = prog.mallocs;
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
	if (home && !ft_strncmp(home, prog.cwd, ft_strlen(home)))
	{
		home = ft_strjoin("~", prog.cwd + ft_strlen(home));
		if (!home)
			return (NULL);
		buff = ft_strjoin("mishell:", home);
		ft_free(home);
	}
	else
		buff = ft_strjoin("mishell:", prog.cwd);
	if (!buff)
		return (NULL);
	home = ft_strjoin(buff, "$ ");
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

	if (!argc && !argv && !envp)
		return (1);
	if (!initprog(envp))
		return (printf("mishell: Init error\n"));
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	//char temp[10];
	while (1)
	{
		prog.cmdli = NULL;
		//printf("%ld\n", read(STDIN_FILENO, temp, 10));
		//perror(strerror(errno));
		stds[0] = dup(STDIN_FILENO);
		stds[1] = dup(STDOUT_FILENO);
		line = ft_readline();
		if (!line)
		{
			return (printf("exit\n"), freeprog(), 0);
		}
		if (!*line)
		{
			ft_free(line);
			continue ;
		}
		prog.cmdli = tokenize(line);
		if (!prog.cmdli)
			return (0);
		i = 0;
		while (i < prog.cmdli->nbcmds)
		{
			if (checkbuiltin(prog.cmdli->cmds[i]) && prog.cmdli->nbcmds == 1)
			{
				prog.cmdli->cmds[i]->path = "BUILTIN";
				cmdbuiltin(prog.cmdli, i);
			}
			else
			{
				prog.cmdli->cmds[i]->path
					= pather(prog.cmdli->cmds[i]->argv[0]);
				if (!prog.cmdli->cmds[i]->path)
					break ;
				if (!cmd(prog.cmdli, i))
					return (0);
			}
			i++;
		}
		// Print path
		//printf("PATH: %s\n", prog.cmdli->cmds[0]->path);
		for (int j = 0; j < i; j++) {
			int	status;
			// pid_t pid = wait(&status);
			waitpid(prog.cmdli->cmds[j]->pid, &status, 0);
			if (prog.cmdli->cmds[j]->pid == prog.cmdli->lastpid)
				setstatus(status);
		}
		i = 0;
		dup2(stds[0], STDIN_FILENO);
		dup2(stds[1], STDOUT_FILENO);
		close(stds[0]);
		close(stds[1]);
		while (i < prog.cmdli->nbcmds)
			ft_free(prog.cmdli->cmds[i++]);
		ft_free(prog.cmdli->cmds);
		ft_free(prog.cmdli);
	}
	return (0);
}

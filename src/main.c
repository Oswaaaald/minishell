/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:42:03 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/14 23:47:29 by fghysbre         ###   ########.fr       */
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

int	writeheredoc(t_prog *prog, char *lim)
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
			ft_malloc_add_ptr(prog, buff);
			if (strcmp(buff, lim) == 0)
				break ;
			write(fd[1], buff, strlen(buff));
			write(fd[1], "\n", 1);
			ft_free(prog, buff);
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

int	cmd(t_prog *prog, t_cmdli *cmdli, int i)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = cmdli->cmds[i];
	if (!openfd(cmd))
		return (0);
	if (cmd->limmiter)
		writeheredoc(prog, cmd->limmiter);
	pid = fork();
	if (!cmdli->cmds[i + 1] && pid > 0)
		cmdli->lastpid = pid;
	if (!pid)
	{
		if (cmdli->cmds[i + 1] || cmd->output)
			dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		if (execve(cmd->path, cmd->argv, prog->minienv))
			exit(EXIT_FAILURE);
	}
	close(cmd->fd[1]);
	if (cmdli->cmds[i + 1])
		dup2(cmd->fd[0], STDIN_FILENO);
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
	t_cmd	*cmd;

	cmd = cmdli->cmds[i];
	
	if (!openfd(cmd))
		return ;
	if (cmd->output)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->input)
		dup2(cmd->fd[0], STDIN_FILENO);
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

char    **getpaths(t_prog *prog, char **env)
{
    int        i;
    char    *pathe;
    char    **res;

    i = -1;
    pathe = NULL;
    while (env[++i])
    {
        if (!ft_strncmp("PATH=", env[i], 5))
            pathe = ft_substr(prog, env[i], 5, ft_strlen(env[i]) - 5);
    }
    if (!pathe)
        return (NULL);
    res = ft_split(prog, pathe, ':');
    ft_free(prog, pathe);
    if (!res)
        return (NULL);
    return (res);
}

char    *pather(t_prog *prog, char *cmd)
{
    char    *buffer;
    char    **paths;
    char    *tmpcmd;
    int        i;

	if (ft_strchr("/.~", cmd[0]))
		return (parsepath(prog, cmd));
    tmpcmd = ft_strjoin(prog, "/", cmd);
    if (!tmpcmd)
        return (NULL);
    paths = getpaths(prog, prog->minienv);
    if (!paths)
        return (ft_free(prog, tmpcmd), NULL);
    i = -1;
    while (paths[++i])
    {
        buffer = ft_strjoin(prog, paths[i], tmpcmd);
        if (!buffer)
            return (ft_free(prog, tmpcmd), free2d(prog, paths), NULL);
        if (access(buffer, X_OK) == 0)
            return (ft_free(prog, tmpcmd), free2d(prog, paths), buffer);
        ft_free(prog, buffer);
    }
    ft_free(prog, tmpcmd);
    free2d(prog, paths);
    return (NULL);
}

void	freeprog(t_prog *prog)
{
	t_list	*tmp;
	t_list	*crnt;

	crnt = prog->mallocs;
	while (crnt)
	{
		tmp = crnt->next;
		if (crnt->content)
			free(crnt->content);
		free(crnt);
		crnt = tmp;
	}
	rl_clear_history();
}

char *ft_readline(t_prog *prog)
{
	char	*home;
	char	*buff;
	char	*ret;
	
	home = ft_getenv(prog, "HOME");
	buff = NULL;
	if (home && !ft_strncmp(home, prog->cwd, ft_strlen(home)))
	{
		home = ft_strjoin(prog, "~", prog->cwd + ft_strlen(home));
		if (!home)
			return (NULL);
		buff = ft_strjoin(prog, "mishell:", home);
		ft_free(prog, home);
	}
	else
		buff = ft_strjoin(prog, "mishell:", prog->cwd);
	if (!buff)
		return (NULL);
	home = ft_strjoin(prog, buff, "$ ");
	ft_free(prog, buff);
	if (!home)
		return (NULL);
	ret = readline(home);
	ft_malloc_add_ptr(prog, ret);
	ft_free(prog, home);
	return(ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_prog	prog;
	int		i;
	t_cmdli	*cmdli;
	char	*line;
	int		stds[2];

	if (!argc && !argv && !envp)
		return (1);
	if (!initprog(&prog, envp))
		return (printf("mishell: Init error\n"));
	//char temp[10];
	while (1)
	{
		//printf("%ld\n", read(STDIN_FILENO, temp, 10));
		//perror(strerror(errno));
		stds[0] = dup(STDIN_FILENO);
		stds[1] = dup(STDOUT_FILENO);
		line = ft_readline(&prog);
		if (!line)
		{
			perror(strerror(errno));
			break ;
		}
		if (!*line)
		{
			ft_free(&prog, line);
			continue ;
		}
		if (!strcmp(line, "exit"))
		{
			freeprog(&prog);
			return (0);
		}
		cmdli = tokenize(&prog, line);
		ft_free(&prog, line);
		if (!cmdli)
			return (0);
		i = 0;
		while (i < cmdli->nbcmds)
		{
			if (checkbuiltin(cmdli->cmds[i]))
			{
				cmdli->cmds[i]->path = "BUILTIN";
				cmdbuiltin(&prog, cmdli, i);
			}
			else
			{
				cmdli->cmds[i]->path
					= pather(&prog, cmdli->cmds[i]->argv[0]);
				if (!cmdli->cmds[i]->path)
					return (0);
				if (!cmd(&prog, cmdli, i))
					return (0);
			}
			i++;
		}
		// Print path
		//printf("PATH: %s\n", cmdli->cmds[0]->path);
		i = 0;
		for (int j = 0; cmdli->cmds[j]; j++) {
			int	status;
			pid_t pid = wait(&status);
			if (pid == cmdli->lastpid)
				setstatus(&prog, status);
		}
		for (int j = 0; cmdli->cmds[j]; j++)
			close(cmdli->cmds[j]->fd[0]);
		dup2(stds[0], STDIN_FILENO);
		dup2(stds[1], STDOUT_FILENO);
		close(stds[0]);
		close(stds[1]);
		while (i < cmdli->nbcmds)
			ft_free(&prog, cmdli->cmds[i++]);
		ft_free(&prog, cmdli->cmds);
		ft_free(&prog, cmdli);
	}
	return (0);
}

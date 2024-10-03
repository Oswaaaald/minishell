/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 00:06:53 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 22:56:25 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getprompt(void)
{
	char	*home;
	char	*buff;

	home = ft_getenv("HOME");
	buff = NULL;
	if (home && *home && !ft_strncmp(home, g_prog.cwd, ft_strlen(home)))
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
	return (home);
}

char	*ft_readline(void)
{
	char	*ret;
	char	*prompt;

	prompt = getprompt();
	if (!prompt)
		return (NULL);
	ret = readline(prompt);
	if (!ret)
		return (NULL);
	ft_malloc_add_ptr(ret);
	ft_free(prompt);
	return (ret);
}

void	setstatus(int status)
{
	if (WIFEXITED(status))
		g_prog.lastexit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_prog.lastexit = WTERMSIG(status) + 128;
}

int	openfder(t_cmd *cmd, int *fd)
{
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
	return (openfder(cmd, fd));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 00:06:53 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/11 12:24:42 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PRBASE "\001\033[32;1m\002mishell\001\033[0m\002:\001\033[34;1m\002"

char	*getprompt(t_prog *prog)
{
	char	*home;
	char	*buff;

	home = ft_getenv(prog, "HOME");
	buff = NULL;
	if (home && *home && !ft_strncmp(home, prog->cwd, ft_strlen(home)))
	{
		home = ft_strjoin(prog, "~", prog->cwd + ft_strlen(home));
		if (!home)
			return (NULL);
		buff = ft_strjoin(prog, PRBASE, home);
		ft_free(prog, home);
	}
	else
		buff = ft_strjoin(prog, PRBASE, prog->cwd);
	if (!buff)
		return (NULL);
	home = ft_strjoin(prog, buff, "\001\033[0m\002$ ");
	ft_free(prog, buff);
	if (!home)
		return (NULL);
	return (home);
}

char	*ft_readline(t_prog *prog)
{
	char	*ret;
	char	*prompt;

	prompt = getprompt(prog);
	if (!prompt)
		return (NULL);
	ret = readline(prompt);
	if (!ret)
		return (NULL);
	ft_malloc_add_ptr(prog, ret);
	ft_free(prog, prompt);
	return (ret);
}

void	setstatus(int status)
{
	if (WIFEXITED(status))
		g_interupt = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_interupt = WTERMSIG(status) + 128;
}

int	openstds(int stds[2])
{
	stds[0] = dup(STDIN_FILENO);
	if (stds[0] == -1)
		return (0);
	stds[1] = dup(STDOUT_FILENO);
	if (stds[1] == -1)
		return (0);
	return (1);
}

int	onlyspace(char	*s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_strchr(" \n	", s[i]))
			return (1);
	}
	return (0);
}

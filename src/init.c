/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:49:58 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/07 15:47:58 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free2d(t_prog *prog, char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		ft_free(prog, arr[i]);
	ft_free(prog, arr);
}

void	setbrutestatus(int stat)
{
	g_interupt = stat;
}

char	**strarrdup(t_prog *prog, char **arr)
{
	int		i;
	char	**res;

	i = -1;
	while (arr[++i])
		;
	res = ft_malloc(prog, (i + 1) * sizeof(char *));
	if (!res)
		return (res);
	i = -1;
	while (arr[++i])
	{
		res[i] = ft_strdup(prog, arr[i]);
		if (!res[i])
			return (free2d(prog, res), NULL);
	}
	res[i] = NULL;
	return (res);
}

int	updateshlvl(t_prog *prog)
{
	char	*buff;
	int		shlvl;

	if (ft_getenv(prog, "SHLVL"))
	{
		shlvl = ft_atoi(ft_getenv(prog, "SHLVL"));
		buff = ft_strjoin(prog, "SHLVL=", ft_itoa(prog, shlvl + 1));
	}
	else
		buff = ft_strdup(prog, "SHLVL=1");
	if (!buff)
		return (0);
	if (miniexport(prog, (char *[]){NULL, buff, NULL}))
		return (ft_free(prog, buff), 0);
	return (ft_free(prog, buff), 1);
}

int	initprog(t_prog *prog, char **envp)
{
	prog->mallocs = NULL;
	if (!*envp)
		prog->minienv = NULL;
	else
		prog->minienv = strarrdup(prog, envp);
	if (!updateshlvl(prog))
		return (free2d(prog, prog->minienv), 0);
	if (!ft_getenv(prog, "PWD"))
	{
		prog->cwd = getcwd(NULL, 0);
		ft_malloc_add_ptr(prog, prog->cwd);
	}
	else
		prog->cwd = ft_strdup(prog, ft_getenv(prog, "PWD"));
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	g_interupt = -3;
	prog->cmdli = NULL;
	return (1);
}

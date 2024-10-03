/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:49:58 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 22:40:38 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free2d(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		ft_free(arr[i]);
	ft_free(arr);
}

void	setbrutestatus(int stat)
{
	g_prog.lastexit = stat;
}

char	**strarrdup(char **arr)
{
	int		i;
	char	**res;

	i = -1;
	while (arr[++i])
		;
	res = ft_malloc((i + 1) * sizeof(char *));
	if (!res)
		return (res);
	i = -1;
	while (arr[++i])
	{
		res[i] = ft_strdup(arr[i]);
		if (!res[i])
			return (free2d(res), NULL);
	}
	res[i] = NULL;
	return (res);
}

int	initprog(char **envp)
{
	char	*buff;

	g_prog.mallocs = NULL;
	if (!envp)
		g_prog.minienv = NULL;
	else
		g_prog.minienv = strarrdup(envp);
	if (ft_getenv("SHLVL"))
		buff = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(ft_getenv("SHLVL")) + 1));
	else
		buff = ft_strdup("SHLVL=1");
	ft_setenv(buff);
	if (!ft_getenv("PWD"))
	{
		g_prog.cwd = getcwd(NULL, 0);
		ft_malloc_add_ptr(g_prog.cwd);
	}
	else
		g_prog.cwd = ft_strdup(ft_getenv("PWD"));
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	signal(SIGTSTP, SIG_IGN);
	g_prog.interupt = 0;
	g_prog.cmdli = NULL;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:49:58 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/20 18:30:44 by mleonet          ###   ########.fr       */
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

	prog.mallocs = NULL;
	prog.minienv = strarrdup(envp);
	if (!prog.minienv)
		return (0);
	if (ft_getenv("SHLVL"))
		buff = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(ft_getenv("SHLVL")) + 1));
	else
		buff = ft_strdup("SHLVL=1");
	ft_setenv(buff);
	prog.cwd = ft_strdup(ft_getenv("PWD"));
	if (!prog.cwd)
	{
		prog.cwd = getcwd(NULL, 0);
		ft_malloc_add_ptr(prog.cwd);
	}
	return (1);
}

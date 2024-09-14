/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:49:58 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/13 18:17:51 by fghysbre         ###   ########.fr       */
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

int	initprog(t_prog *prog, char **envp)
{
	char	*buff;

	prog->mallocs = NULL;
	prog->minienv = strarrdup(prog, envp);
	if (!prog->minienv)
		return (0);
	if (ft_getenv(prog, "SHLVL"))
		buff = ft_strjoin(prog, "SHLVL=", ft_itoa(prog, ft_atoi(ft_getenv(prog, "SHLVL")) + 1));
	else
		buff = ft_strdup(prog, "SHLVL=1");
	ft_setenv(prog, buff);
	prog->cwd = ft_strdup(prog, ft_getenv(prog, "PWD"));
	if (!prog->cwd)
	{
		prog->cwd = getcwd(NULL, 0);
		ft_malloc_add_ptr(prog, prog->cwd);
	}
	
	return (1);
}

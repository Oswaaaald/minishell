/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:49:58 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/12 14:52:28 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free2d(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	**strarrdup(char **arr)
{
	int		i;
	char	**res;

	i = -1;
	while (arr[++i])
		;
	res = malloc((i + 1) * sizeof(char *));
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

int	initprog(t_prog *prog, char **envp)
{
	char	*buff;

	prog->minienv = strarrdup(envp);
	if (!prog->minienv)
		return (0);
	if (ft_getenv(prog, "SHLVL"))
		buff = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(ft_getenv(prog, "SHLVL")) + 1));
	else
		buff = ft_strdup("SHLVL=1");
	ft_setenv(prog, buff);
	prog->cwd = ft_strdup(ft_getenv(prog, "PWD"));
	if (!prog->cwd)
		prog->cwd = getcwd(NULL, 0);
	
	return (1);
}

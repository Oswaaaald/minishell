/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd-pather.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:47:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/10 14:05:50 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**getpaths(t_prog *prog, char **env)
{
	int		i;
	char	*pathe;
	char	**res;

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

char	*patherpart2(t_prog *prog, int i, char **paths, char *tmpcmd)
{
	char	*buffer;

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

char	*pather(t_prog *prog, char *cmd)
{
	char	**paths;
	char	*tmpcmd;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (parsepath(prog, cmd));
	tmpcmd = ft_strjoin(prog, "/", cmd);
	if (!tmpcmd)
		return (NULL);
	paths = getpaths(prog, prog->minienv);
	if (!paths)
		return (ft_free(prog, tmpcmd), NULL);
	i = -1;
	return (patherpart2(prog, i, paths, tmpcmd));
}

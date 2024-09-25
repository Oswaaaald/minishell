/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:47:16 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/25 16:47:32 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	paths = getpaths(g_prog.minienv);
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
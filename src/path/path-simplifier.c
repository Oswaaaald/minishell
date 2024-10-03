/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path-simplifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:19:39 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 21:36:25 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pathexpander(char *path)
{
	char	*home;
	char	*ret;

	if (!path)
		path = "~";
	if (path[0] == '~' && (path[1] == '/' || !path[1]))
	{
		home = ft_getenv("HOME");
		if (!home)
			return (write(2, "mishell: Home env not set\n", 26), NULL);
		ret = ft_strjoin(home, path + 1);
		return (ret);
	}
	else if (path[0] != '~' && path[0] != '/')
	{
		home = g_prog.cwd;
		ret = strcjoin(home, path, '/');
		return (ret);
	}
	return (ft_strjoin(path, ""));
}

int	isonlyslash(char *path)
{
	int	i;

	i = -1;
	while (path[++i])
	{
		if (path[i] != '/')
			return (0);
	}
	return (1);
}

char	*parsepather(t_list *tmp, t_list *buf, t_list *pathlst, char *path)
{
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, "..", -1))
		{
			buf = tmp->next;
			if (lstbef(pathlst, tmp))
				ft_lstpop(&pathlst, lstbef(pathlst, tmp));
			ft_lstpop(&pathlst, tmp);
			tmp = buf;
		}
		else if (!ft_strncmp((char *)tmp->content, ".", -1))
		{
			buf = tmp->next;
			ft_lstpop(&pathlst, tmp);
			tmp = buf;
		}
		else
			tmp = tmp->next;
	}
	ft_free(path);
	if (pathlst == NULL)
		return (ft_strdup("/"));
	return (lstjoin(pathlst));
}

char	*parsepath(char *path)
{
	char	**paths;
	t_list	*pathlst;
	t_list	*tmp;
	t_list	*buf;

	if (!ft_strncmp(path, "-", -1))
		return (ft_strdup("-"));
	path = pathexpander(path);
	if (!path)
		return (NULL);
	if (isonlyslash(path))
		return (ft_free(path), ft_strdup("/"));
	paths = ft_split(path, '/');
	if (!paths)
		return (ft_free(path), NULL);
	pathlst = arrtolst(paths);
	if (!pathlst)
		return (ft_free(path), free2d(paths), NULL);
	tmp = pathlst;
	buf = NULL;
	return (parsepather(tmp, buf, pathlst, path));
}

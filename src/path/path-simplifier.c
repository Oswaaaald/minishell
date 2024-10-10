/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path-simplifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:19:39 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/10 15:26:14 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pathexpander(t_prog *prog, char *path)
{
	char	*home;
	char	*ret;

	if (!path)
		path = "~";
	if (path[0] == '~' && (path[1] == '/' || !path[1]))
	{
		home = ft_getenv(prog, "HOME");
		if (!home || !*home)
			return (write(2, "mishell: Home env not set\n", 26), NULL);
		ret = ft_strjoin(prog, home, path + 1);
		return (ret);
	}
	else if (path[0] != '~' && path[0] != '/')
	{
		home = prog->cwd;
		ret = strcjoin(prog, home, path, '/');
		return (ret);
	}
	return (ft_strjoin(prog, path, ""));
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

char	*parsepather(t_prog *prog, t_list *tmp, t_list *pathlst, char *path)
{
	t_list	*buf;

	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, "..", -1))
		{
			buf = tmp->next;
			if (lstbef(pathlst, tmp))
				ft_lstpop(prog, &pathlst, lstbef(pathlst, tmp));
			ft_lstpop(prog, &pathlst, tmp);
			tmp = buf;
		}
		else if (!ft_strncmp((char *)tmp->content, ".", -1))
		{
			buf = tmp->next;
			ft_lstpop(prog, &pathlst, tmp);
			tmp = buf;
		}
		else
			tmp = tmp->next;
	}
	ft_free(prog, path);
	if (pathlst == NULL)
		return (ft_strdup(prog, "/"));
	return (lstjoin(prog, pathlst));
}

char	*parsepath(t_prog *prog, char *path)
{
	char	**paths;
	t_list	*pathlst;
	t_list	*tmp;

	if (!ft_strncmp(path, "-", -1))
		return (ft_strdup(prog, "-"));
	path = pathexpander(prog, path);
	if (!path)
		return (NULL);
	if (isonlyslash(path))
		return (ft_free(prog, path), ft_strdup(prog, "/"));
	paths = ft_split(prog, path, '/');
	if (!paths)
		return (ft_free(prog, path), NULL);
	pathlst = arrtolst(prog, paths);
	if (!pathlst)
		return (ft_free(prog, path), free2d(prog, paths), NULL);
	tmp = pathlst;
	return (parsepather(prog, tmp, pathlst, path));
}

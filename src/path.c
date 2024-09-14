/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:19:39 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/13 17:23:55 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*arrtolst(t_prog *prog, char **arr)
{
	int		i;
	t_list	*tmp;
	t_list	*final;

	i = -1;
	final = NULL;
	while (arr[++i])
	{
		tmp = ft_lstnew((void *) arr[i]);
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&final, tmp);
	}
	ft_free(prog, arr);
	return (final);
}

char	*strcjoin(t_prog *prog, char *s1, char *s2, char fil)
{
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2 || !fil)
		return (NULL);
	ret = ft_malloc(prog, strlen(s1) + strlen(s2) + 2);
	if (!ret)
		return (NULL);
	while (s1[++i])
		ret[i] = s1[i];
	ret[i] = fil;
	while ((++i || i == 0) && s2[++j])
		ret[i] = s2[j];
	ret[i] = 0;
	return (ret);
}

char	*pathjoin(t_prog *prog, char *s1, char *s2, int last)
{
	char	*ret;
	int		i;
	int		j;

	if (s1 == NULL)
		s1 = "/";
	ret = ft_malloc(prog, strlen(s1) + strlen(s2) + 1 + (last == 0));
	i = -1;
	j = -1;
	while (s1[++i])
		ret[i] = s1[i];
	i--;
	while ((++i || i == 0) && s2[++j])
		ret[i] = s2[j];
	if (!last)
	{
		ret[i] = '/';
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*lstjoin(t_prog *prog, t_list *lst)
{
	char	*buff;
	char	*temp;
	t_list	*tmp;

	tmp = lst;
	buff = NULL;
	while (tmp)
	{
		temp = buff;
		buff = pathjoin(prog, buff, (char *) tmp->content, tmp->next == NULL);
		if (temp)
			ft_free(prog, temp);
		tmp = tmp->next;
	}
	ft_lstclear(prog, &lst, ft_free);
	return (buff);
}

char	*pathexpander(t_prog *prog, char *path)
{
	char	*home;
	char	*ret;

	if (!path)
		path = "~";
	if (path[0] == '~' && (path[1] == '/' || !path[1]))
	{
		home = ft_getenv(prog, "HOME");
		if (!home)
			return (printf("mishell: Home env not set\n"), NULL);
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

char	*parsepath(t_prog *prog, char *path)
{
	char	**paths;
	t_list	*pathlst;
	t_list	*tmp;
	t_list	*buf;

	path = pathexpander(prog, path);
	if (!path)
		return (NULL);
	paths = ft_split(prog, path, '/');
	pathlst = arrtolst(prog, paths);
	if (!pathlst)
		return (NULL);
	tmp = pathlst;
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
	return (lstjoin(prog, pathlst));
}

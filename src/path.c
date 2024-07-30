/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:19:39 by fghysbre          #+#    #+#             */
/*   Updated: 2024/07/30 12:38:24 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list  *arrtolst(char **arr)
{
    int i;
    t_list  *tmp;
    t_list  *final;

    i = -1;
    final = NULL;
    while (arr[++i])
    {
        tmp = ft_lstnew((void *) arr[i]);
        if (!tmp)
            return (NULL);
        ft_lstadd_back(&final, tmp);
    }
    free(arr);
    return (final);
}

char    *strcjoin(char *s1, char *s2, char fil)
{
    char    *ret;
    int     i;
    int     j;
    ret = malloc(strlen(s1) + strlen(s2) + 2);
    i = -1;
    j = -1;
    while (s1[++i])
        ret[i] = s1[i];
    ret[i] = fil;
    while ((++i || i == 0) && s2[++j])
        ret[i] = s2[j];
    ret[i] = 0;
    return (ret);
}

char    *pathjoin(char *s1, char *s2, int last)
{
    char    *ret;
    int     i;
    int     j;

    if (s1 == NULL)
        s1 = "/";
    ret = malloc(strlen(s1) + strlen(s2) + 1 + (last == 0));
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

char    *lstjoin(t_list *lst)
{
    char    *buff;
    char    *temp;
    t_list  *tmp;

    tmp = lst;
    buff = NULL;
    while (tmp)
    {
        temp = buff;
        buff = pathjoin(buff, (char *) tmp->content, tmp->next == NULL);
        if (temp)
            free(temp);
        tmp = tmp->next;
    }
    ft_lstclear(&lst, free);
    return (buff);
}

t_list  *lstbef(t_list *list, t_list *elem)
{
    t_list  *tmp;

    tmp = list;
    if (tmp == elem)
        return (NULL);
    while (tmp->next)
    {
        if (tmp->next == elem)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

void    lstpop(t_list **list, t_list *elem)
{
    t_list  *bef;

    bef = lstbef(*list, elem);
    if (bef)
        bef->next = elem->next;
    else
        *list = elem->next;
    ft_lstdelone(elem, free);
}

char    *pathExpander(char *path)
{
	char	*home;
	char 	*ret;
    
    if (!path)
        path = "~";
    if (path[0] == '~' && (path[1] == '/' || !path[1]))
	{
		home = getenv("HOME");
		ret = ft_strjoin(home, path + 1);
		return (ret);
	}
    else if (path[0] == '.')
    {
        home = getenv("PWD");
        ret = strcjoin(home, path, '/');
        return (ret);
    }
	return (ft_strjoin(path, ""));
}

char    *parsepath(char *path)
{
    path = pathExpander(path);
    char    **paths = ft_split(path, '/');
    t_list  *pathlst = arrtolst(paths);
    t_list  *tmp = pathlst;
    t_list  *buf;
    while (tmp)
    {
        if (!ft_strncmp((char *)tmp->content, "..", -1))
        {
            buf = tmp->next;
            if (lstbef(pathlst, tmp))
                lstpop(&pathlst, lstbef(pathlst, tmp)); 
            lstpop(&pathlst, tmp);
            tmp = buf;
        }
        else if (!ft_strncmp((char *)tmp->content, ".", -1))
        {
            buf = tmp->next;
            lstpop(&pathlst, tmp);
            tmp = buf;
        }
        else
            tmp = tmp->next;
    }
    return (lstjoin(pathlst));
}
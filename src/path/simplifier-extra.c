/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplifier-extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:53:24 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/07 14:31:43 by fghysbre         ###   ########.fr       */
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
	ret = ft_malloc(prog, ft_strlen(s1) + ft_strlen(s2) + 2);
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
	ret = ft_malloc(prog, ft_strlen(s1) + ft_strlen(s2) + 1 + (last == 0));
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
		if (!buff)
			return (free(temp), NULL);
		if (temp)
			ft_free(prog, temp);
		tmp = tmp->next;
	}
	ft_lstclear(prog, &lst, ft_free);
	return (buff);
}

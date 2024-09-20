/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:14:56 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/20 19:07:00 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_prog	g_prog;

void	ft_malloc_add_ptr(void *ptr)
{
	t_list	*link;

	link = ft_lstnew(ptr);
	if (!link)
		return ;
	ft_lstadd_back(&g_prog.mallocs, link);
}

void	*ft_malloc(size_t size)
{
	void	*res;
	t_list	*link;

	res = malloc(size);
	if (!res)
		return (NULL);
	link = ft_lstnew(res);
	if (!link)
		return (free(res), NULL);
	ft_lstadd_back(&g_prog.mallocs, link);
	return (res);
}

void	ft_free(void *ptr)
{
	t_list	*tmp;
	t_list	*bef;

	tmp = g_prog.mallocs;
	while (tmp && tmp->content != ptr)
		tmp = tmp->next;
	if (tmp)
	{
		bef = lstbef(g_prog.mallocs, tmp);
		if (bef)
			bef->next = tmp->next;
		else
			g_prog.mallocs = tmp->next;
		free(tmp);
	}
	free(ptr);
}

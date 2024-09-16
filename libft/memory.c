/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:14:56 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 16:14:58 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_prog	prog;

void	ft_malloc_add_ptr(void *ptr)
{
	t_list	*link;

	link = ft_lstnew(ptr);
	if (!link)
		return ;
	ft_lstadd_back(&prog.mallocs, link);
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
	ft_lstadd_back(&prog.mallocs, link);
	return (res);
}

void	ft_free(void *ptr)
{
	t_list	*tmp;
	t_list	*bef;

	tmp = prog.mallocs;
	while (tmp && tmp->content != ptr)
		tmp = tmp->next;
	if (tmp)
	{
		bef = lstbef(prog.mallocs, tmp);
		if (bef)
			bef->next = tmp->next;
		else
			prog.mallocs = tmp->next;
		free(tmp);
	}
	free(ptr);
}
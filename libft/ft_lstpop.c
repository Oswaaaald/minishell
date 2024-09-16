/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:03:23 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:34 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*lstbef(t_list *list, t_list *elem)
{
	t_list	*tmp;

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

void	ft_lstpop(t_list **list, t_list *elem)
{
	t_list	*bef;

	bef = lstbef(*list, elem);
	if (bef)
		bef->next = elem->next;
	else
		*list = elem->next;
	ft_lstdelone(elem, ft_free);
}
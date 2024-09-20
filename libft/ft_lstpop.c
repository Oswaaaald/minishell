/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:03:23 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/20 18:21:11 by mleonet          ###   ########.fr       */
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

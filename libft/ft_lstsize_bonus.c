/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:32:01 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:46:09 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*list;
	int		c;

	if (!lst)
		return (0);
	list = lst;
	c = 1;
	while (list->next)
	{
		c++;
		list = list->next;
	}
	return (c);
}

// Test Main
/* 
int	main(void)
{
	t_list	*lst = ft_lstnew("Test");
	t_list	**lst_ptr = &(lst);

	ft_lstadd_front(lst_ptr, ft_lstnew("Please"));
	ft_lstadd_front(lst_ptr, ft_lstnew("Thanks"));
	printf("%d\n", ft_lstsize(lst_ptr[0]));
}
 */
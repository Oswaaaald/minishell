/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:02:19 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 16:02:51 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_prog *prog, t_list **lst,
	void (*del)(t_prog *prog, void *))
{
	t_list	*tmp;
	t_list	*crnt;

	if (!lst || !del)
		return ;
	crnt = *lst;
	while (crnt)
	{
		tmp = crnt->next;
		ft_lstdelone(prog, crnt, del);
		crnt = tmp;
	}
	*lst = (void *)0;
}

// Test Main

/* void	test(void *ptr)
{
	ptr = (void *)0;
}

int	main(void)
{
	t_list *lst = ft_lstnew("Test1");
	t_list *lst2 = ft_lstnew("Test2");
	t_list *lst3 = ft_lstnew("Test3");
	t_list **lst_ptr = &(lst);
	t_list *current;

	current = lst_ptr[0];
	ft_lstadd_back(lst_ptr, lst2);
	ft_lstadd_back(lst_ptr, lst3);
	ft_lstclear(lst_ptr, &test);
} */
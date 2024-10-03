/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:59:51 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:45:53 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	if (!f || !lst)
		return ;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}

// Test Main

/* void	put(void *ptr)
{
	printf("%s\n", ptr);
}

int	main(void)
{
	t_list	*lst;
	t_list	*lst2;
	t_list	*lst3;
	t_list	**lst_ptr;
	t_list	*current;

	lst = ft_lstnew("Test1");
	lst2 = ft_lstnew("Test2");
	lst3 = ft_lstnew("Test3");
	lst_ptr = &(lst);
	current = lst_ptr[0];
	ft_lstadd_back(lst_ptr, lst2);
	ft_lstadd_back(lst_ptr, lst3);
	ft_lstiter(lst, &put);
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:15:06 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/23 12:23:30 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_last;

	if (!lst || !new)
		return ;
	if (!(lst[0]))
	{
		lst[0] = new;
	}
	else
	{
		lst_last = lst[0];
		lst_last = ft_lstlast(lst_last);
		lst_last->next = new;
	}
}

// Test Main

/* int	main(void)
{
	t_list *lst = ft_lstnew("Test");
	t_list **lst_ptr = &(lst);
	t_list *current;

	printf("Old list\n");
	ft_lstadd_front(lst_ptr, ft_lstnew("Please"));
	current = lst_ptr[0];
	while (current->next)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
	printf("%s\n", current->content);
	current = lst_ptr[0];
	ft_lstadd_back(lst_ptr, ft_lstnew("Thanks"));
	printf("\nNew list\n");
	while (current->next)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
	printf("%s\n", current->content);
} */

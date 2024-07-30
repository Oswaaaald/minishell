/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:56:46 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/18 16:56:46 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*res;

	if (!lst)
		return ((void *)0);
	res = lst;
	while (res->next)
		res = res->next;
	return (res);
}

// Test Main
/* 
int	main(void)
{
	t_list	*lst = ft_lstnew("Test");
	t_list	**lst_ptr = &(lst);

	ft_lstadd_front(lst_ptr, ft_lstnew("Please"));
	ft_lstadd_front(lst_ptr, ft_lstnew("Thanks"));
	printf("%s\n", ft_lstlast(lst_ptr[0])->content);
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:14:32 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/23 12:17:31 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (!res)
		return ((void *)0);
	res->content = content;
	res->next = NULL;
	return (res);
}

// Test Main
/* 
int	main(void)
{
	t_list	*lst;

	lst = ft_lstnew("Test");
	printf("%s\n", lst->content);
} */

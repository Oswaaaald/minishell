/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:14:32 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 16:46:00 by fghysbre         ###   ########.fr       */
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

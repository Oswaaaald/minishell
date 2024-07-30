/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:13:04 by fghysbre          #+#    #+#             */
/*   Updated: 2023/10/31 16:07:36 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*lst_ptr;
	void	*ret;

	if (!f || !del || !lst)
		return (NULL);
	lst_ptr = NULL;
	while (lst)
	{
		ret = f(lst->content);
		tmp = ft_lstnew(ret);
		if (!tmp)
		{
			free(ret);
			return (ft_lstclear(&lst_ptr, del), (void *)0);
		}
		ft_lstadd_back(&lst_ptr, tmp);
		lst = lst->next;
	}
	return (lst_ptr);
}
// Test Main

/* #include <string.h>

void	*ft_map(void *ct)
{
	void	*c;
	char	*pouet;
	int		i;

	c = ct;
	i = -1;
	pouet = (char *)c;
	while (pouet[++i])
		if (pouet[i] == 'o')
			pouet[i] = 'a';
	return (c);
}

void	ft_del(void *content)
{
	free(content);
}

int	main(int argc, const char *argv[])
{
	t_list	*elem;
	t_list	*elem2;
	t_list	*elem3;
	t_list	*elem4;
	t_list	*list;
	t_list	**lstptr;
	char	*str;
	char	*str2;
	char	*str3;
	char	*str4;
	int		i;

	str = strdup("lorem");
	str2 = strdup("ipsum");
	str3 = strdup("dolor");
	str4 = strdup("sit");
	elem = ft_lstnew(str);
	lstptr = &elem;
	elem2 = ft_lstnew(str2);
	elem3 = ft_lstnew(str3);
	elem4 = ft_lstnew(str4);
	if (!elem || !elem2 || !elem3 || !elem4)
	{
		system("leaks a.out");
		return (0);
	}
	ft_lstadd_back(lstptr, elem2);
	ft_lstadd_back(lstptr, elem3);
	ft_lstadd_back(lstptr, elem4);
	if (1 == 1)
	{
		if (!(list = ft_lstmap(elem, &ft_map, &ft_del)))
		{
			system("leaks a.out");
			return (0);
		}
		if (list == elem)
			write(1, "A new list is not returned\n", 27);
		i = 0;
		printf("%s\n", list->content);
		while (list->next)
		{
			list = list->next;
			printf("%s\n", list->content);
			i++;
		}
	}
	system("leaks a.out");
	return (0);
} */

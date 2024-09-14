#include "libft.h"

void	ft_malloc_add_ptr(t_prog *prog, void *ptr)
{
	t_list	*link;

	link = ft_lstnew(ptr);
	if (!link)
		return ;
	ft_lstadd_back(&prog->mallocs, link);
}

void	*ft_malloc(t_prog *prog, size_t size)
{
	void	*res;
	t_list	*link;

	res = malloc(size);
	if (!res)
		return (NULL);
	link = ft_lstnew(res);
	if (!link)
		return (free(res), NULL);
	ft_lstadd_back(&prog->mallocs, link);
	return (res);
}

void	ft_free(t_prog *prog, void *ptr)
{
	t_list	*tmp;
	t_list	*bef;

	tmp = prog->mallocs;
	while (tmp && tmp->content != ptr)
		tmp = tmp->next;
	if (tmp)
	{
		bef = lstbef(prog->mallocs, tmp);
		if (bef)
			bef->next = tmp->next;
		else
			prog->mallocs = tmp->next;
		free(tmp);
	}
	free(ptr);
}
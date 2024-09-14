/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:58:35 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/13 16:33:11 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_prog *prog, t_list *lst, void (*del)(t_prog *, void *))
{
	if (!lst || !del)
		return ;
	if (lst->content)
		del(prog, lst->content);
	free(lst);
}

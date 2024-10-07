/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:58:35 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 16:03:00 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_prog *prog, t_list *lst,
	void (*del)(t_prog *prog, void *))
{
	if (!lst || !del)
		return ;
	if (lst->content)
		del(prog, lst->content);
	free(lst);
}

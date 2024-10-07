/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer-extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:23:28 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/04 14:19:41 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*freem(t_prog *prog, char **str, int a)
{
	int	i;

	i = -1;
	while (str[++i] && i < a)
		ft_free(prog, str[i]);
	ft_free(prog, str);
	return ((void *)0);
}

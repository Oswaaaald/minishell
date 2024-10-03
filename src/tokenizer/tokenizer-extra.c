/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer-extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:23:28 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 21:56:38 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*freem(char **str, int a)
{
	int	i;

	i = -1;
	while (str[++i] && i < a)
		ft_free(str[i]);
	ft_free(str);
	return ((void *)0);
}

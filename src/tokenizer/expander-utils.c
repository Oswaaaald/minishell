/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:31:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 22:31:32 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	translationorwhatevahhandler(char **buff, char *str, int i)
{
	char	*tmp;

	if (i == 0)
		return (1);
	str[i] = 0;
	if (!*buff)
		*buff = ft_strdup(str);
	else
	{
		tmp = *buff;
		*buff = ft_strjoin(*buff, str);
		ft_free(tmp);
	}
	str[i] = '$';
	return (i + 1);
}

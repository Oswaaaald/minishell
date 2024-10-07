/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:31:14 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/07 13:51:45 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	translationorwhatevahhandler(t_prog *prog, char **buff, char *str, int i)
{
	char	*tmp;

	str[i] = 0;
	if (!*buff)
		*buff = ft_strdup(prog, str);
	else
	{
		tmp = *buff;
		*buff = ft_strjoin(prog, *buff, str);
		ft_free(prog, tmp);
	}
	str[i] = '$';
	return (i + 1);
}

int	getendofvar(char *str, int i, int si)
{
	while (str[++i])
	{
		if (str[i] == '?' && si == i - 1)
		{
			i++;
			break ;
		}
		if ((i == si + 1 && !(ft_isalpha(str[i]) || str[i] == '_'))
			|| (i > 0 && !(ft_isalnum(str[i]) || str[i] == '_')))
			break ;
	}
	return (i);
}

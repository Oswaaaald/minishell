/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:05:01 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/30 12:39:28 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checkredir(char *str, int *i)
{
	if (ft_strchr("<>", str[*i]) && str[*i] == str[*i + 1])
		(*i)++;
	while (str[(*i)++] && ft_strchr(" 	\n", str[*i]))
		;
	if (!str[*i])
		return (
			printf("mishell: syntax error near unexpected token `newline'\n"),
			0);
	if (ft_strchr("<>|", str[*i]))
		return (printf("mishell: syntax error near unexpected token `%c'\n",
			str[*i]), 0);
	return (1);
}

int	checksyntax(char *str)
{
	int	i;
	int qu[2];

	i = -1;
	ft_memset(qu, 0, sizeof(int) * 2);
	while (str[++i])
	{
		if (str[i] == '\'' && !qu[1])
			qu[0] = !qu[0];
		else if (str[i] == '"' && !qu[0])
			qu[1] = ! qu[1];
		if (!qu[0] && !qu[1] && ft_strchr("<>|", str[i]))
		{
			if (!checkredir(str, &i))
				return (0);
		}
	}
	return (1);
}

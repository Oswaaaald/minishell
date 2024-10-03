/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:05:01 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 23:07:15 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	putunexpect(char *str, int i)
{
	int	len;

	len = 1;
	if ((ft_strchr(">|", str[i]) && str[i] == str[i + 1])
		|| (str[i] == '<' && ft_strchr("<>", str[i + 1])))
		len++;
	write(2, "mishell: syntax error near unexpected token `", 45);
	write(2, str + i, len);
	write(2, "'\n", 2);
}

static int	checkredir(char *str, int *i)
{
	char	oldchar;

	if ((str[*i] == '>' && str[*i] == str[*i + 1])
		|| (str[*i] == '<' && ft_strchr("<>", str[*i + 1])))
		(*i)++;
	oldchar = str[*i];
	while (str[(*i)++] && ft_strchr(" 	\n", str[*i]))
		;
	if (!str[*i])
		return (write(2, "mishell: syntax error near ", 28),
			write(2, "unexpected token `newline'\n", 27), 0);
	if ((ft_strchr("<>", oldchar) && ft_strchr("<>|", str[*i]))
		|| (oldchar == '|' && str[*i] == '|'))
		return (putunexpect(str, *i), 0);
	(*i)--;
	return (1);
}

int	checksyntaxer(char *str, int i, int qu[2], int first)
{
	while (str[++i])
	{
		if (str[i] == '\'' && !qu[1])
			qu[0] = !qu[0];
		else if (str[i] == '"' && !qu[0])
			qu[1] = ! qu[1];
		if (!qu[0] && !qu[1] && ft_strchr("<>|", str[i]))
		{
			if (first && str[i] == '|')
				return (putunexpect(str, i), 0);
			if (!checkredir(str, &i))
				return (0);
		}
		if (!ft_strchr(" \t\n", str[i]))
			first = 0;
	}
	if (qu[0] || qu[1])
		return (write(2, "mishell: syntax error near unexpected token `", 45),
			write(2, "newline'\n", 9), 0);
	return (1);
}

int	checksyntax(char *str)
{
	int	i;
	int	qu[2];
	int	first;

	i = -1;
	first = 1;
	ft_memset(qu, 0, sizeof(int) * 2);
	return (checksyntaxer(str, i, qu, first));
}

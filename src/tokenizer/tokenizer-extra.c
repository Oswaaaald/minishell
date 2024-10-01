/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer-extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:23:28 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 23:38:07 by fghysbre         ###   ########.fr       */
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

int	unfinisheder(int qu[2], char *lastchar, char *startchar)
{
	if (qu[0] || qu[1])
		return (1);
	if (lastchar - startchar <= 2)
		return (0);
	if (lastchar[0] == '|')
		return (1);
	return (0);
}

int	unfinished(char *line)
{
	char	*lastchar;
	char	*startchar;
	int		i;
	int		qu[2];

	i = -1;
	if (!line)
		return (0);
	startchar = NULL;
	ft_memset(qu, 0, sizeof(int) * 2);
	while (line[++i])
	{
		if (ft_isprint(line[i]) && !(line[i] == ' ') && !(line[i] == '	'))
		{
			if (!startchar)
				startchar = &line[i];
			lastchar = &line[i];
		}
		if (line[i] == '"' && !qu[0])
			qu[1] = !qu[1];
		if (line[i] == '\'' && !qu[1])
			qu[0] = !qu[0];
	}
	return (unfinisheder(qu, lastchar, startchar));
}

int	finish(char **lineptr)
{
	char	*buff;
	char	*tmp;

	g_prog.status = ST_FINISH;
	buff = readline("> ");
	if (!buff)
		return (0);
	tmp = *lineptr;
	*lineptr = ft_strjoin(tmp, "\n");
	ft_free(tmp);
	tmp = *lineptr;
	*lineptr = ft_strjoin(tmp, buff);
	ft_free(tmp);
	ft_free(buff);
	g_prog.status = ST_IDLE;
	return (1);
}

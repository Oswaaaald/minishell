/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:49:56 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/03 00:04:36 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expandvar(t_prog *prog, char **buff, char *str, int i)
{
	int		si;
	char	*tmp;
	char	c;

	si = i;
	str[i] = '\0';
	if (!*buff)
		*buff = ft_strdup(str);
	else
	{
		tmp = *buff;
		*buff = ft_strjoin(*buff, str);
		free(tmp);
	}
	str[i] = '$';
	while (str[++i])
	{
		if ((i == si + 1 && !(ft_isalpha(str[i]) || str[i] == '_'))
			|| (i > 0 && !(ft_isalnum(str[i]) || str[i] == '_')))
			break ;
	}
	c = str[i];
	str[i] = '\0';
	if (ft_getenv(prog, &str[si + 1]))
		*buff = ft_strjoin(*buff, ft_getenv(prog, &str[si + 1]));
	str[i] = c;
	return (i - 1);
}

char	*expand(t_prog *prog, char *str)
{
	int		i;
	char	*buff;
	int		quotes[2];
	int		last;

	i = -1;
	buff = NULL;
	quotes[0] = 0;
	quotes[1] = 0;
	last = 0;
	while (str[++i])
	{
		if (str[i] == '"' && !quotes[0])
			quotes[1] = !quotes[1];
		if (str[i] == '\'' && !quotes[1])
			quotes[0] = !quotes[0];
		if (str[i] == '$' && !quotes[0])
		{
			last = expandvar(prog, &buff, &(str[last]), i - last);
			i = last;
		}
	}
	if (!buff)
		return (ft_strdup(str));
	return (ft_strjoin(buff, &str[last + 1]));
}

int	unfinished(char *line)
{
	char	*lastchar;
	char	*startchar;
	int		i;

	i = -1;
	if (!line)
		return (0);
	startchar = NULL;
	while (line[++i])
	{
		if (ft_isprint(line[i]) && !(line[i] == ' ') && !(line[i] == '	'))
		{
			if (!startchar)
				startchar = &line[i];
			lastchar = &line[i];
		}
	}
	if (lastchar - startchar <= 2)
		return (0);
	if ((lastchar[0] == '&' && lastchar[-1] == '&') || (lastchar[0] == '|'))
		return (1);
	return (0);
}

void	finish(char **lineptr)
{
	char	*buff;
	char	*tmp;

	buff = readline("> ");
	if (!buff)
		return ;
	tmp = *lineptr;
	*lineptr = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = *lineptr;
	*lineptr = ft_strjoin(tmp, buff);
	free(tmp);
	free(buff);
}

void	tokenize(t_prog *prog, char *line)
{
	char	*eline;

	while (unfinished(line))
		finish(&line);
	if (!line)
		return ;
	add_history(line);
	eline = expand(prog, line);
	printf("%s\n", eline);
}

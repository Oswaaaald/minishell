/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:49:56 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/06 18:41:55 by mleonet          ###   ########.fr       */
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

int	nbcmds(char *line)
{
	int	i;
	int	ret;

	i = -1;
	ret = 1;
	while (line[++i])
	{
		if (line[i] == '|' && line [i + 1] != '|')
			ret++;
	}
	return (ret);
}

char	**arrayaddback(char **currentarr, char *str)
{
	char	**retarr;
	int		i;

	i = 0;
	while (currentarr && currentarr[i])
		i++;
	retarr = (char **) malloc(sizeof(char *) * (i + 2));
	if (!retarr)
		return (NULL);
	i = 0;
	while (currentarr && currentarr[i])
	{
		retarr[i] = currentarr[i];
		i++;
	}
	retarr[i] = str;
	retarr[i + 1] = NULL;
}

char	*pullarg(char *str, int qu[2], int *i)
{
	int	j;

	j = -1;
	while (str[*i + ++j])
	{
		if (ft_strchr("<|>", ))
			;
	}
}

void	arghandle(t_cmdli *ret, char *arg, int *cmdi)
{
	int	i;
	int	qu[2];

	i = -1;
	qu[0] = 0;
	qu[1] = 0;
	while (arg[++i])
	{
		if (arg[i] == '"' && !qu[0])
			qu[1] = !qu[1];
		else if (arg[i] == '\'' && !qu[1])
			qu[0] = !qu[0];
		if (!ft_strchr("|<>\"'", arg[i]))
			;
	}
}

void	getcmds(t_cmdli *ret, char **args)
{
	int	i;
	int	cmdi;

	i = -1;
	cmdi = 0;
	while (args[++i])
	{
		arghandle(ret, args[i], &cmdi);
	}
}

//splitargs
static int	nwords(char const *s)
{
	int	count;
	int	nword;
	int	i;
	int	qu[2];

	count = 0;
	nword = 1;
	i = -1;
	qu[0] = 0;
	qu[1] = 0;
	while (s[++i])
	{
		if (s[i] == '"' && !qu[0])
			qu[1] = !qu[1];
		else if (s[i] == '\'' && !qu[1])
			qu[0] = !qu[0];
		if (!ft_strchr(" \t\n", s[i]) && nword)
		{
			count++;
			nword = 0;
		}
		if (ft_strchr(" \t\n", s[i]) && !(qu[0] || qu[1]) && !nword)
			nword = 1;
	}
	return (count);
}

static int	wordlen(char const *s, int ind)
{
	int	count;
	int	qu[2];

	count = 0;
	qu[0] = 0;
	qu[1] = 0;
	while ((!ft_strchr(" \t\n", s[ind]) || qu[0] || qu[1]) && s[ind])
	{
		if (s[ind] == '"' && !qu[0])
			qu[1] = !qu[1];
		else if (s[ind] == '\'' && !qu[1])
			qu[0] = !qu[0];
		count++;
		ind++;
	}
	return (count);
}

static void	*freem(char **str, int a)
{
	int	i;

	i = -1;
	while (str[++i] && i < a)
		free(str[i]);
	free(str);
	return ((void *)0);
}

static char	**split_process(char const *s, char **res)
{
	int	nword;
	int	i;
	int	a;

	nword = 1;
	i = -1;
	a = -1;
	while (s[++a])
	{
		if (!ft_strchr(" \t\n", s[a]) && nword)
		{
			res[++i] = (char *)malloc(wordlen(s, a) + 1);
			if (!(res[i]))
				return (freem(res, i));
			ft_strlcpy(res[i], s + a, wordlen(s, a) + 1);
			a = a + wordlen(s, a) - 1;
		}
		nword = (ft_strchr(" \t\n", s[a]) != 0);
	}
	res[++i] = (void *)0;
	return (res);
}

char	**splitline(char const *s)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc((nwords(s) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (split_process(s, res));
}

t_cmdli	*actuallytokenize(char *line)
{
	t_cmdli	*ret;
	char	**splitargs;

	ret = malloc(sizeof(t_cmdli));
	if (!ret)
		return (ret);
	ret->nbcmds = nbcmds(line);
	ret->cmds = malloc(sizeof(t_cmd) * (ret->nbcmds + 1));
	splitargs = splitline(line);
	getcmds(ret, splitargs);
}

t_cmdli	*tokenize(t_prog *prog, char *line)
{
	char	*eline;
	t_cmdli	*ret;

	while (unfinished(line))
		finish(&line);
	if (!line)
		return ;
	add_history(line);
	eline = expand(prog, line);
	ret = actuallytokenize(prog, eline);
	printf("%s\n", eline);
}

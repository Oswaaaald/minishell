/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:49:56 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 15:43:28 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (qu[0] || qu[1])
		return (1);
	if (lastchar - startchar <= 2)
		return (0);
	if (lastchar[0] == '|')
		return (1);
	return (0);
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
	retarr = (char **) ft_malloc(sizeof(char *) * (i + 2));
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
	ft_free(currentarr);
	return (retarr);
}

char	*pullarg(char *str, int qu[2], int *i)
{
	int		j;
	char	*arg;

	j = 0;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (!str[*i])
		return (NULL);
	while (str[*i + j])
	{
		if (str[*i + j] == '"' && !qu[0])
			qu[1] = !qu[1];
		else if (str[*i + j] == '\'' && !qu[1])
			qu[0] = !qu[0];
		else if (!qu[0] && !qu[1] && str[*i + j] == '|')
			break ;
		j++;
	}
	arg = ft_substr(str, *i, j);
	*i += j - 1;
	return (arg);
}


void	arghandle(t_cmdli *ret, char *arg, int *cmdi)
{
	int		i;
	int		qu[2];
	char	*tmp;
	t_cmd	*current_cmd;

	i = -1;
	ft_memset(qu, 0, sizeof(int) * 2);
	current_cmd = ret->cmds[*cmdi];
	while (arg[++i])
	{
		if (arg[i] == '"' && !qu[0])
			qu[1] = !qu[1];
		else if (arg[i] == '\'' && !qu[1])
			qu[0] = !qu[0];
		if (!qu[0] && !qu[1] && arg[i] == '|')
		{
			(*cmdi)++;
			current_cmd = ret->cmds[*cmdi];
		}
		else if (arg[i] != '|')
		{
			tmp = pullarg(arg, qu, &i);
			current_cmd->argv = arrayaddback(current_cmd->argv, tmp);
		}
	}
}


void	getcmds(t_cmdli *ret, char **args)
{
	int		i;
	int		cmdi;

	i = 0;
	cmdi = 0;
	while (args[i])
	{
		arghandle(ret, args[i], &cmdi);
		i++;
	}
}

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
		ft_free(str[i]);
	ft_free(str);
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
			res[++i] = (char *)ft_malloc(wordlen(s, a) + 1);
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
	res = (char **)ft_malloc((nwords(s) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (split_process(s, res));
}

int	openredir(t_cmd *cmd)
{
	int	fd;

	if (cmd->input)
	{
		fd = open(cmd->input, O_RDONLY, 0777);
		if (!fd)
			return (0);
		close(fd);
	}
	if (cmd->output)
	{
		if (cmd->outappend)
			fd = open(cmd->output, O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			fd = open(cmd->output, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			return (0);
		close(fd);
	}
	return (1);
}


t_cmdli	*actuallytokenize(char *line)
{
	t_cmdli	*ret;
	char	**splitargs;
	int		i;

	if (!checksyntax(line))
		return (setstatus(2), NULL);
	ret = ft_malloc(sizeof(t_cmdli));
	if (!ret)
		return (NULL);
	ret->nbcmds = nbcmds(line);
	ret->cmds = ft_malloc(sizeof(t_cmd *) * (ret->nbcmds + 1));
	if (!ret->cmds)
		return (ft_free(ret), NULL);
	i = 0;
	while (i < ret->nbcmds)
	{
		ret->cmds[i] = ft_malloc(sizeof(t_cmd));
		if (!ret->cmds[i])
		{
			while (i-- > 0)
				ft_free(ret->cmds[i]);
			ft_free(ret->cmds);
			ft_free(ret);
			return (NULL);
		}
		ret->cmds[i]->argv = NULL;
		ret->cmds[i]->env = NULL;
		ret->cmds[i]->input = NULL;
		ret->cmds[i]->output = NULL;
		ret->cmds[i]->limmiter = NULL;
		ret->cmds[i]->outappend = 0;
		ret->cmds[i]->path = NULL;
		ft_memset(ret->cmds[i]->fd, 0, sizeof(int) * 2);
		ret->cmds[i]->pid = 0;
		i++;
	}
	ret->cmds[ret->nbcmds] = NULL;
	splitargs = splitline(line);
	if (!*splitargs)
	{
		ret->nbcmds = 0;
		return (ft_free(ret->cmds[0]), ret);
	}
	getcmds(ret, splitargs);
	free2d(splitargs);
	i = -1;
	while (ret->cmds[++i])
	{
		if (!getredirs(ret, ret->cmds[i]))
			return (NULL);
		ret->cmds[i]->path = pather(ret->cmds[i]->argv[0]);
	}
	if (!checkcmd(ret))
		return (NULL);
	return (ret);
}

t_cmdli	*tokenize(char *line)
{
	char	*eline;
	t_cmdli	*ret;
	int		togg;

	togg = 0;
	while (unfinished(line))
	{
		if (!finish(&line))
		{
			if (!togg)
				ft_free(line);
			return (NULL);
		}
		togg = 1;
	}
	if (!line)
		return (NULL);
	add_history(line);
	eline = expand(line);
	ret = actuallytokenize(eline);
	ft_free(eline);
	if (!togg)
		ft_free(line);
	return (ret);
}

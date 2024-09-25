/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:49:56 by fghysbre          #+#    #+#             */
/*   Updated: 2024/09/25 16:54:16 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expandvar(char **buff, char *str, int i)
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
		ft_free(tmp);
	}
	str[i] = '$';
	while (str[++i])
	{
		if (str[i] == '?' && si == i - 1)
		{
			i++;
			break ;
		}
		if ((i == si + 1 && !(ft_isalpha(str[i]) || str[i] == '_'))
			|| (i > 0 && !(ft_isalnum(str[i]) || str[i] == '_')))
		{
			if (si == i - 1)
			{
				tmp = *buff;
				*buff = ft_strjoin(*buff, "$");
				ft_free(tmp);
				return (i - 1);
			}
			break ;
		}
	}
	c = str[i];
	str[i] = '\0';
	if (ft_getenv(&str[si + 1]))
		*buff = ft_strjoin(*buff, ft_getenv(&str[si + 1]));
	str[i] = c;
	return (i);
}

char	*expand(char *str)
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
			last = last + expandvar(&buff, &(str[last]), i - last);
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
	while (str[*i + j])
	{
		if (str[*i + j] == '"' && !qu[0])
			qu[1] = !qu[1];
		else if (str[*i + j] == '\'' && !qu[1])
			qu[0] = !qu[0];
		else if (!qu[0] && !qu[1] && ft_strchr("<|>", str[*i + j]))
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

	i = 0;
	qu[0] = 0;
	qu[1] = 0;
	current_cmd = ret->cmds[*cmdi];
	while (arg[i])
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
		else if (!qu[0] && !qu[1] && (arg[i] == '<' || arg[i] == '>'))
		{
			tmp = pullarg(arg, qu, &i);
			if (arg[i - 1] == '<')
				current_cmd->input = tmp;
			else
				current_cmd->output = tmp;
		}
		else if (!ft_strchr("|<>", arg[i]))
		{
			tmp = pullarg(arg, qu, &i);
			current_cmd->argv = arrayaddback(current_cmd->argv, tmp);
		}
		i++;
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

int	openredir(t_cmd *cmd) {
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
		if (!fd)
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
		ret->cmds[i]->path = pather(ret->cmds[i]->argv[0]);
	if (!checkcmdli(ret))
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

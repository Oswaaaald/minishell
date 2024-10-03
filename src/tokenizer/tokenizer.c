/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:49:56 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/03 22:24:51 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

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

int	malloccmdli(t_cmdli *ret, int i)
{
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
			return (0);
		}
		ret->cmds[i]->argv = NULL;
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
	return (1);
}

t_cmdli	*fillcmdli(char *line, t_cmdli *ret, int i)
{
	char	**splitargs;
	int		tmp;

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
			return (setbrutestatus(1), NULL);
		remquotes(ret->cmds[i]);
		ret->cmds[i]->path = pather(ret->cmds[i]->argv[0]);
	}
	tmp = checkcmd(ret);
	if (tmp)
		return (setbrutestatus(tmp), NULL);
	return (ret);
}

t_cmdli	*actuallytokenize(char *line)
{
	t_cmdli	*ret;
	int		i;

	if (!checksyntax(line))
		return (setbrutestatus(2), NULL);
	ret = ft_malloc(sizeof(t_cmdli));
	if (!ret)
		return (NULL);
	ret->nbcmds = nbcmds(line);
	ret->cmds = ft_malloc(sizeof(t_cmd *) * (ret->nbcmds + 1));
	if (!ret->cmds)
		return (ft_free(ret), NULL);
	i = 0;
	malloccmdli(ret, i);
	return (fillcmdli(line, ret, i));
}

t_cmdli	*tokenize(char *line)
{
	char	*eline;
	t_cmdli	*ret;
	int		togg;

	togg = 0;
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

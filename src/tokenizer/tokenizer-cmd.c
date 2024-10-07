/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer-cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:26:01 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/07 16:33:43 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	nbcmds(char *line)
{
	int	i;
	int	ret;
	int	qu[2];

	i = -1;
	ret = 1;
	ft_memset(qu, 0, sizeof(int) * 2);
	while (line[++i])
	{
		if (line[i] == '\'' && !qu[1])
			qu[0] = !qu[0];
		else if (line[i] == '"' && !qu[0])
			qu[1] = !qu[1];
		if (!qu[0] && !qu[1] && line[i] == '|' && line [i + 1] != '|')
			ret++;
	}
	return (ret);
}

char	**arrayaddback(t_prog *prog, char **currentarr, char *str)
{
	char	**retarr;
	int		i;

	i = 0;
	while (currentarr && currentarr[i])
		i++;
	retarr = (char **) ft_malloc(prog, sizeof(char *) * (i + 2));
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
	ft_free(prog, currentarr);
	return (retarr);
}

char	*pullarg(t_prog *prog, char *str, int qu[2], int *i)
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
		if (str[*i + j] == '"' && !qu[0] && j)
			qu[1] = !qu[1];
		else if (str[*i + j] == '\'' && !qu[1] && j)
			qu[0] = !qu[0];
		else if (!qu[0] && !qu[1] && str[*i + j] == '|')
			break ;
		j++;
	}
	arg = ft_substr(prog, str, *i, j);
	*i += j - 1;
	return (arg);
}

int	arghandle(t_prog *prog, t_cmdli *ret, char *arg, int *cmdi)
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
		updatequotes(qu, arg[i]);
		if (!qu[0] && !qu[1] && arg[i] == '|')
		{
			(*cmdi)++;
			current_cmd = ret->cmds[*cmdi];
		}
		else if (arg[i] != '|')
		{
			tmp = pullarg(prog, arg, qu, &i);
			if (!tmp)
				return (0);
			current_cmd->argv = arrayaddback(prog, current_cmd->argv, tmp);
		}
	}
	return (1);
}

int	getcmds(t_prog *prog, t_cmdli *ret, char **args)
{
	int		i;
	int		cmdi;

	i = 0;
	cmdi = 0;
	while (args[i])
	{
		if (!arghandle(prog, ret, args[i], &cmdi))
			return (0);
		i++;
	}
	return (1);
}

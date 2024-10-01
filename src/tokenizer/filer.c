/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:58:39 by fghysbre          #+#    #+#             */
/*   Updated: 2024/10/01 14:06:56 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strarrpop(t_cmd *cmd, int i)
{
	int		j;
	char	**tmp;
	int		togg;

	j = -1;
	while (cmd->argv[++j])
		;
	tmp = ft_malloc(sizeof(char *) * (j));
	if (!tmp)
		return 0;
	j = -1;
	togg = 0;
	while (cmd->argv[++j])
	{
		if (i == j)
			togg = 1;
		if (i == j)
			continue ;
		tmp[j - togg] = cmd->argv[j];
	}
	tmp[j - togg] = NULL;
	ft_free(cmd->argv);
	cmd->argv = tmp;
	return (1);
}

int	remlastmeta(t_cmd *cmd, int i)
{
	int		j;
	char	*ret;

	j = ft_strlen(cmd->argv[i]) - 1;
	if (ft_strchr("<>", cmd->argv[i][j - 1]))
		j--;
	cmd->argv[i][j] = 0;
	ret = ft_strdup(cmd->argv[i]);
	if (!ret)
		return (0);
	cmd->argv[i][j] = '<';
	ft_free(cmd->argv[i]);
	cmd->argv[i] = ret;
	return (1);
}

int	remfromnext(t_cmd *cmd, int *i, int k)
{
	char	*tmp;

	if (!cmd->argv[*i][k])
	{
		if (!strarrpop(cmd, *i))
			return (0);
	}
	else
	{
		tmp = ft_strdup(cmd->argv[*i] + k);
		if (!tmp)
			return (0);
		ft_free(cmd->argv[*i]);
		cmd->argv[*i] = tmp;
	}
	if ((ft_strchr("<>", cmd->argv[*i - 1][0]) && !cmd->argv[*i - 1][1]) ||
		(ft_strchr("<>", cmd->argv[*i - 1][0]) && 
		ft_strchr("<>", cmd->argv[*i - 1][1]) && !cmd->argv[*i - 1][2]))
	{
		if (!strarrpop(cmd, *i - 1))
			return (0);
	}
	else
	{
		if (!remlastmeta(cmd, *i - 1))
			return (0);
		return (1);
	}
	(*i)--;
	return (1);
}

char	*getredirfromnext(t_cmd *cmd, int *i)
{
	char	*ret;
	int		k;
	int		qu[2];

	k = -1;
	(*i)++;
	if (!cmd->argv[*i] || ft_strchr("&<>()", cmd->argv[*i][0]))
		return (printf("mishell: syntax error near unexpected token `%c'",
				cmd->argv[*i][0]), NULL);
	ft_memset(qu, 0, sizeof(int) * 2);
	while (cmd->argv[*i][++k]){
		if (cmd->argv[*i][k] == '\'' && !qu[1])
			qu[0] = !qu[0];
		if (cmd->argv[*i][k] == '"' && !qu[0])
			qu[1] = !qu[1];
		if (!qu[0] && !qu[1] && ft_strchr("<>", cmd->argv[*i][k]))
			break ;
	}
	ret = ft_substr(cmd->argv[*i], 0, k);
	if (!ret)
		return (NULL);
	if (!remfromnext(cmd, i, k))
		return (free(ret), NULL);
	return (ret);
}

char	*ft_strndup(char *str, int n)
{
	char	*ret;
	int		i;

	ret = ft_malloc(n + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < n) {
		ret[i] = str[i];
	}
	ret[i] = 0;
	return (ret);
}

char	*stromit(char *str, int start, int len)
{
	char	*ret;
	int		i;

	ret = ft_malloc(ft_strlen(str) - len + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < start)
		ret[i] = str[i];
	i--;
	while (str[++i + len])
		ret[i] = str[i + len];
	ret[i] = 0;
	return (ret);
}

int	remfromcurrent(t_cmd *cmd, int *i, int *j, int k)
{
	(*j)--;
	k++;
	char	*tmp;
	if (*j > 0 && ft_strchr("<>", cmd->argv[*i][*j - 1]))
	{
		(*j)--;
		k++;
	}
	if (*j == 0 && !cmd->argv[*i][k])
	{
		if (!strarrpop(cmd, *i))
			return (0);
	}
	else
	{
		tmp = stromit(cmd->argv[*i], *j, k);
		if (!tmp)
			return (0);
		ft_free(cmd->argv[*i]);
		cmd->argv[*i] = tmp;
	}
	return (1);
}

char	*getredirfromcurrent(t_cmd *cmd, int *i, int *j)
{
	char	*ret;
	int		k;
	int		qu[2];

	k = -1;
	(*j)++;
	if (!cmd->argv[*i] || ft_strchr("&<>()", cmd->argv[*i][*j]))
		return (printf("mishell: syntax error near unexpected token `%c'",
				cmd->argv[*i][*j]), NULL);
	ft_memset(qu, 0, sizeof(int) * 2);
	while (cmd->argv[*i][++k + *j]){
		if (cmd->argv[*i][k + *j] == '\'' && !qu[1])
			qu[0] = !qu[0];
		if (cmd->argv[*i][k + *j] == '"' && !qu[0])
			qu[1] = !qu[1];
		if (!qu[0] && !qu[1] && ft_strchr("<>", cmd->argv[*i][k + *j]))
			break ;
	}
	ret = ft_substr(cmd->argv[*i], *j, k);
	if (!ret)
		return (NULL);
	if (!remfromcurrent(cmd, i, j, k))
		return (ft_free(ret), NULL);
	return (ret);
}

void	setredirs(t_cmd *cmd, char *str, char *metachar)
{

	if ((metachar[0] == '<' && metachar[1] != '<') || (metachar[0] == '<' && metachar[1] == '>'))
	{
		if (cmd->input)
			ft_free(cmd->input);
		cmd->input = str;
		if (cmd->limmiter)
		{
			ft_free(cmd->limmiter);
			cmd->limmiter = NULL;
		}
	}
	else if (metachar[0] == '<' && metachar[1] == '<')
	{
		if (cmd->limmiter)
			ft_free(cmd->limmiter);
		cmd->limmiter = str;
		if (cmd->input)
		{
			ft_free(cmd->input);
			cmd->input = NULL;
		}
	}
	else if (metachar[0] == '>')
	{
		if (cmd->output)
			ft_free(cmd->output);
		cmd->output = str;
		if (metachar[1] == '>')
			cmd->outappend = 1;
		else
			cmd->outappend = 0;
	}
}

int	getredir(t_cmd *cmd, int *i, int *j)
{
	int	oldj;
	int	oldi;
	char	metachar[2];

	oldj = *j;
	oldi = *i;
	metachar[0] = cmd->argv[oldi][oldj];
	metachar[1] = cmd->argv[oldi][oldj + 1];
	if (cmd->argv[*i][*j + 1] && ft_strchr("<>", cmd->argv[*i][*j + 1]))
		*j = *j + 1;
	char	*str;
	if (!cmd->argv[*i][*j + 1])
		str = getredirfromnext(cmd, i);
	else
		str = getredirfromcurrent(cmd, i, j);
	if (!str)
		return (0);
	setredirs(cmd, str, metachar);
	return (1);
}

int	getredirs(t_cmdli *cmdli, t_cmd *cmd)
{
	int	qu[2];

	ft_memset(qu, 0, sizeof(int) * 2);
	for (int i = 0; cmd->argv[i]; i++) {
		for (int j = 0; cmd->argv[i][j]; j++) {
			if (cmd->argv[i][j] == '\'' && !qu[1])
				qu[0] = !qu[0];
			if (cmd->argv[i][j] == '"' && !qu[0])
				qu[1] = !qu[1];
			if (!qu[0] && !qu[1] && ft_strchr("<>", cmd->argv[i][j]))
			{
				if (!getredir(cmd, &i, &j))
					return (0);
				if (!cmd->argv[i])
					break ;
				j--;
			}
		}
		if (!cmd->argv[i])
			break ;
	}
	if (!checkfiles(cmdli) || !cmd->argv[0])
		return (0);
	return (1);
}
